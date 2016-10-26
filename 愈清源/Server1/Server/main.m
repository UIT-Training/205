//
//  main.m
//  Server
//
//  Created by 俞清源 on 16/10/10.
//  Copyright © 2016年 俞清源. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "socketListen.h"

NSMutableArray *saveUser;

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        saveUser = [[NSMutableArray alloc]initWithCapacity:20];
        
        socketListen *start = [socketListen alloc];
        
        [start socketStart];
    }
    return 0;
}
