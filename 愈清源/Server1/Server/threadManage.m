//
//  threadManage.m
//  Server
//
//  Created by 俞清源 on 16/10/10.
//  Copyright © 2016年 俞清源. All rights reserved.
//

#import "threadManage.h"

@implementation threadManage

-(void)manageThread:(SaveSocket *)clientSocket
{
//    [saveUser addObject:clientSocket];
    
    socketListen *sendMessage;
    
    sendMessage = [socketListen alloc];
    
    dispatch_queue_t queue = dispatch_queue_create("1", DISPATCH_QUEUE_CONCURRENT);
    
    dispatch_queue_t queue2 = dispatch_queue_create("2", DISPATCH_QUEUE_CONCURRENT);
    
    dispatch_async(queue, ^{
        while(1)
        {
            void (^saveInfo)(void) = ^(void){                           //更新用户信息
                [saveUser removeObject:clientSocket];
                [saveUser addObject:clientSocket];
            };
            
            int (^dealRecv)(void) = ^(void){                            //block复用
                
                memset(recvMessage, 0, 1024);
                
                if(recv(clientSocket._UserSocket, recvMessage, 1024, 0) <= 0){
                    NSLog(@"跳出线程");
                    [saveUser removeObject:clientSocket];
                    return 0;
                }
                
                NSInteger len = strlen(recvMessage);
                
                recvMessage[len] = '\0';
                
                NSLog(@"%s",recvMessage);
                
                NSString *transfer = [[NSString alloc]initWithFormat:@"%s",recvMessage];
                
                recvFromUser = [NSMutableString new];                  //删除前缀后的字符串
                recvFromUserChange = [NSMutableString new];            //消息前缀
                
                [recvFromUser appendString:transfer];
                [recvFromUserChange appendString:transfer];
                
                [recvFromUser deleteCharactersInRange:NSMakeRange(0,10)];
                
                [recvFromUserChange deleteCharactersInRange:[recvFromUserChange rangeOfString:recvFromUser]];
                
                NSLog(@"%@",recvFromUserChange);
                
                return 1;
            };
            
            if(dealRecv() == 0){
                break;
            }
            
            if([recvFromUserChange isEqualToString:@"<talk_All>"])
            {
                clientSocket._talkAll = 0;      //群聊
                saveInfo();
                while(1)
                {
                    if(dealRecv() == 0){
                        break;
                    }
                    if([recvFromUserChange isEqualToString:@"<log__out>"]){
                        NSLog(@"退出");
                        clientSocket._talkAll = -1;
                        saveInfo();
                        
                        send(clientSocket._UserSocket, "&", 1, 0);
                        break;
                    }
                    else{
                    dispatch_sync(queue2, ^{
                                        sendToAll = [[NSString alloc]initWithFormat:@"%@: %@",[online backuserName] ,recvFromUser];
                                        [sendMessage recvMessage:sendToAll];
                                        });
                    }
                }
            }
            
            if([recvFromUserChange isEqualToString:@"<talk_one>"]){
                
            }
            
            if([recvFromUserChange isEqualToString:@"<loginUse>"]){
                
                NSLog(@"登录");
                
                NSString *transMessage;
                
                transMessage = [[NSString alloc]initWithFormat:@"select *from new_schema.userID_PassWord where %@",recvFromUser];
                
                int flag = 0;
                
                online = [mysqlManage alloc];
                
                flag = [online SignIn:transMessage :recvFromUser];
                
                if(flag == 1)
                {
                    clientSocket._UserID = [online backuserName];       //保存用户ID
                    
                    clientSocket._flag = 1;                     //表示用户在线
                    
                    saveInfo();
                    
                    send(clientSocket._UserSocket,"1",1,0);
                }
                else{
                    send(clientSocket._UserSocket,"0",1,0);
                }
            }
            
            if([recvFromUserChange isEqualToString:@"<register>"]){
                
                NSLog(@"注册");
                NSString *transMessage;
                
                transMessage = [[NSString alloc]initWithFormat:@"%@",recvFromUser];
                
                int flag = 0;
                
                mysqlManage *newPassport = [mysqlManage alloc];
                
                flag = [newPassport Register:transMessage];
                
                if(flag == 1)
                {
                    NSLog(@"保存成功");
                }
            }
            if([recvFromUserChange isEqualToString:@"<To__meun>"]){
                [saveUser removeObject:clientSocket];
            }
            if([recvFromUserChange isEqualToString:@"<_online_>"]){
                //获得好友在线人数
                int num = [sendMessage getFriendNum];
                NSString *transfer = [[NSString alloc]initWithFormat:@"%d",num];
                send(clientSocket._UserSocket, [transfer UTF8String], [transfer length], 0);
            }
        }
    });
}

@end
