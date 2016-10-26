//
//  socketListen.m
//  Server
//
//  Created by 俞清源 on 16/10/13.
//  Copyright © 2016年 俞清源. All rights reserved.
//

#import "socketListen.h"

@implementation socketListen

-(int)socketStart{
    struct sockaddr_in server_addr;
    server_addr.sin_len = sizeof(struct sockaddr_in);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1111);
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.122");
    bzero(&(server_addr.sin_zero),8);
    
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket error");
        return 1;
    }
    
    int bind_result = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (bind_result == -1) {
        perror("bind error");
        return 1;
    }
    
    if (listen(server_socket, 5) == -1) {
        perror("listen error");
        return 1;
    }
    
    struct sockaddr_in client_address;
    socklen_t address_len;
    threadManage *dealThread;
    
    while(1)
    {
        userSocket = [SaveSocket new];
        userSocket._UserSocket = accept(server_socket, (struct sockaddr *)&client_address, &address_len);
        NSLog(@"新用户进入");
        
        dealThread = [threadManage new];
        
        [dealThread manageThread:userSocket];
        
    }
    return 0;
}
-(int)recvMessage:(NSString*)messageToAll{
    NSInteger len = [messageToAll length];
    NSLog(@"传输数据");
    for(userSocket in saveUser){
        NSLog(@"%@,%d",userSocket._UserID,userSocket._flag);
        if(userSocket._flag == 1&&userSocket._talkAll == 0){
            NSLog(@"%@",userSocket._UserID);
            send(userSocket._UserSocket, [messageToAll UTF8String], len, 0);
        }
    }
    return 0;
}
-(int)getFriendNum{
    int num = 0;
    for(userSocket in saveUser){
        if(userSocket._flag == 1){
            num++;
        }
    }
    return --num;
}

@end
