#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Epoll.h"
#include "Socket.h"
#include "Client.h"
#include "Server.h"

class Controller{
public:
    void Start(); 
    void End(); 
private: 
    Socket socket;  //socket 实例 
    Epoll epoll;    //epoll 实例 
    Client clients[CLIENT_NUM];     //声明一大堆客户
    struct sockaddr_in clientAddr;    //客户端clientaddr信息
    int ep_events_count;    //就绪事件的数目
    int socketfd;    //socket文件描述符
    int epollfd;    //Epoll文件描述符
    int clients_count;       //初始化的clients数量
    list<Client *> clients_list;     //用户容器
    void Chatting();    //实现聊天
    void Add_client();  //添加用户
    void Receive_message(int evtfd);      //接收新消息
    void Boardcast(int evtfd);    //广播——群发
    void Prompt();      //提示新人加入聊天
};
#endif