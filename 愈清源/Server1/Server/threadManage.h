//
//  threadManage.h
//  Server
//
//  Created by 俞清源 on 16/10/10.
//  Copyright © 2016年 俞清源. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <sys/socket.h>
#import <arpa/inet.h>
#import <mysql.h>
#import "mysqlManage.h"
#import "socketListen.h"
#import "SaveSocket.h"

extern NSMutableArray *saveUser;

@interface threadManage : NSObject{
   char recvMessage[1024];
    NSString *sendToAll;
    mysqlManage *online;
   __block NSMutableString *recvFromUser;
   __block NSMutableString *recvFromUserChange;
}

-(void)manageThread:(SaveSocket *)clientSocket;

@end
