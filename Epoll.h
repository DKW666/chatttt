#ifndef EPOLL_H
#define EPOLL_H
#include "Server.h"

class Epoll{
public: 
    //Epoll 初始化
    int Initialize(int socketfd);

    //增加epoll-wait
    void Add_epoll_wait(int client_socket_fd);

    //阻塞等待
    int Wait_evt(epoll_event *events);

    //return epollfd
    int getEpollfd(){
        return epollfd;
    }
private:
    //epoll 文件描述符
    int epollfd;
    
    //epoll模式
    bool ET_LT;
};
#endif