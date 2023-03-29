#ifndef CONFIGDEF_H
#define CONFIGDEF_H
/*********************************************************************
*@file       ConfigDef.h
*@brief      管理枚举enum、定义define、QString...
*@author     sgrH
*@date       11/15/22
*********************************************************************/
///@ 网路请求消息结构
typedef struct _tagNetMessage
{
    QString _type;  // 类型
    int  _flag;     // 标识
    QString _url;   // 接口Url
    QString _method;  // 请求方式
    QByteArray _byte; // 参数
}NetMessage;

// 请求接口
/// @brief 发送聊天消息
#define API_POST_ASK_ACTION "http://www.xxxx.com/tztv/ask_action.php"

// 请求类型标识
/// @brief 消息类型(用来在发送和接收网络请求时，区分是哪种消息类型)
namespace RequestType {
#define REQUEST_TYPE_ASK_ACTION "ask_action" // 直播间发送文本消息
};

#endif // CONFIGDEF_H
