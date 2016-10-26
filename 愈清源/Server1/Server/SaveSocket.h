//
//  SaveSocket.h
//  Server
//
//  Created by 俞清源 on 16/10/22.
//  Copyright © 2016年 俞清源. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SaveSocket : NSObject{
    int UserSocket;     //用户的套接字
    int flag;           //是否在线
    int talkAll;        //1为私聊,0为群聊,-1处于别的界面
    NSString *UserID;   //用户名称
}

@property int _UserSocket;
@property int _flag;
@property int _talkAll;
@property NSString *_UserID;

@end
