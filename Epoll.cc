#include "Epoll.h"
#include "wrap.cc"

int Epoll::Initialize(int socketfd){
    //创建epoll文件描述符，在系统内核中创建事件表
    //创建的事件表由红黑树作结构
    epollfd = Create_epoll(EPOLL_SIZE);

    //向时间表中添加事件
    //int epoll_ctl(int efpd,int op,int sockid,struct epoll_event *event);
    Add_epoll_wait(socketfd);

    return epollfd;
}


void Epoll::Add_epoll_wait(int listen_fd){
    struct epoll_event ep_evt;
    ep_evt.data.fd = listen_fd;     //需要监听的文件描述符
    ep_evt.events = EPOLLIN;  //阻塞等待
    Epoll_CTL(epollfd, listen_fd, &ep_evt); 
}

int Epoll::Wait_evt(epoll_event *events){
    //函数原型int epoll_wait(int epfd,struct epoll_event *events,int maxevents,int timeout);
    //timeout -1 为无限等待
    int evts_count = epoll_wait(epollfd, events, EPOLL_SIZE, -1);
    return evts_count;
}