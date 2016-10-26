//
//  mysqlManage.h
//  Server
//
//  Created by 俞清源 on 16/10/10.
//  Copyright © 2016年 俞清源. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <mysql.h>

@interface mysqlManage : NSObject{
    MYSQL mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    NSString *userName;
}

-(int)SignIn:(NSString*)clientMessage :(NSMutableString *)origin;

-(int)Register:(NSString*)nameMessage;

-(NSString*)backuserName;

@property NSString *_userName;

@end