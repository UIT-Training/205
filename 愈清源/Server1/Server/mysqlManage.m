//
//  mysqlManage.m
//  Server
//
//  Created by 俞清源 on 16/10/10.
//  Copyright © 2016年 俞清源. All rights reserved.
//

#import "mysqlManage.h"

@implementation mysqlManage

-(int)SignIn:(NSString*)clientMessage :(NSMutableString *)origin{
    mysql_init(&mysql);
                                  //ip地址      用户名   密码      数据库名称
    if(!mysql_real_connect(&mysql, "127.0.0.1", "root","970517", "new_schema",0, nil, 0)){
        NSLog(@"connecting to Mysql error:%d from %s \n",mysql_errno(&mysql),mysql_error(&mysql));
        NSLog(@"数据库连接失败");
    }
    else{
        NSLog(@"successful");
    }
    mysql_query(&mysql,[clientMessage UTF8String]);
    
    result = mysql_store_result(&mysql);
    
    row = mysql_fetch_row(result);
    
    NSInteger num = mysql_num_rows(result);
    
    mysql_free_result(result);
    
    mysql_close(&mysql);
    
    NSString *compare;
    NSString *messageOrigin = [[NSString alloc]initWithFormat:@"%@",origin];
    
    if(num != 0)
    {
        compare = [[NSString alloc]initWithFormat:@"ID='%s' and Pass_Word like '%s'",row[0],row[1]];
    }
    else{
        NSLog(@"查询失败");
        return -1;
    }
    
    if([compare isEqualToString:messageOrigin]){
        NSLog(@"查询成功");
        userName = [[NSString alloc]initWithFormat:@"%s",row[0]];
        return 1;
    }
    else{
        NSLog(@"查询失败");
        return -1;
    }
}

-(int)Register:(NSString*)nameMessage{
    mysql_init(&mysql);
                                    //ip地址      用户名   密码      数据库名称
    if(!mysql_real_connect(&mysql, "127.0.0.1", "root","970517", "new_schema",0, nil, 0)){
        NSLog(@"connecting to Mysql error:%d from %s \n",mysql_errno(&mysql),mysql_error(&mysql));
        NSLog(@"数据库连接失败");
    }
    else{
        NSLog(@"successful");
    }
    
    mysql_query(&mysql,[nameMessage UTF8String]);
    
    result = mysql_store_result(&mysql);
    
    mysql_free_result(result);
    
    mysql_close(&mysql);
    
    
    
    return 1;
}

-(NSString*)backuserName
{
    return userName;
}
@end
