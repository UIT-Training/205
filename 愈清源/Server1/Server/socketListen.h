//
//  socketListen.h
//  Server
//
//  Created by 俞清源 on 16/10/13.
//  Copyright © 2016年 俞清源. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <pthread.h>
#import <sys/socket.h>
#import <arpa/inet.h>
#import <mysql.h>
#import "threadManage.h"
#import "SaveSocket.h"

extern NSMutableArray *saveUser;

@interface socketListen : NSObject{
    SaveSocket *userSocket;
}

-(int)socketStart;

-(int)recvMessage:(NSString*)messageToAll;

-(int)getFriendNum;

@end
