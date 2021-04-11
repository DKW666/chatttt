//封装错误函数
#include "Server.h"

int Create_socket(int Pfamily, int type, int protocol){
    int n = socket(Pfamily, type, protocol);
    if (n < 0){
        perror("socket create error");
        exit(-1);
    }
    cout << "socket created" << endl;
    return n;
}

void Bind_socket(int sfd, struct sockaddr *saddr, int size){
    int n = bind(sfd, saddr, size);
    if (n < 0) {
        perror("bind error");
        exit(-1);
    }
    cout << "socket binded" << endl;
}

void Listen_socket(int sfd, int log){
    int n = listen(sfd, log);
    if (n < 0) {
        perror("listen error");
        exit(-1);
    }
    cout << "start listening" << endl;
}

int Accept_socket(int sfd, struct sockaddr *caddr, socklen_t *length){
    int n = accept(sfd, caddr, length);
    if(n < 0) {
        perror("accept error");
        exit(-1);
    }
    cout << "accept socket" << endl;
    return n;
}

int Create_epoll(int size){
    int n = epoll_create (EPOLL_SIZE);
    if (n < 0) {
        perror("epoll create error");
        exit(-1);
    }
    cout << "epoll created" << endl;
    return n;
}

void Epoll_CTL(int epfd, int lfd, struct epoll_event *evt){
    int n = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, evt); 
    if (n < 0){
        perror("epoll controll error");
        exit(-1);
    }
    fcntl(epfd, F_SETFL, fcntl(epfd, F_GETFD, 0)| O_NONBLOCK); 
    cout << "socket fd added to epoll" << endl;
}

// int Epoll_wait(int efd, epoll_event events, int size, int timeout){
//     int n = epoll_wait(efd, &events, size, timeout);
//     if (n < 0) {
//         perror("epoll_wait error");
//         exit(-1);
//     }
//     cout << " epolle_wait done: " << n << endl;
//     return n;
// }

int Send_buffer(int cfd, char buf[], int size, int flasgs){
    int n = send(cfd, buf, size, flasgs);
    if (n < 0) {
        perror("write error");
        exit(-1);
    }
    cout << "buffer wrotten" << endl;
    return n;
}

int Receive_buffer(int fd, char buf[], int size, int flags){
    int n = recv(fd, buf, size, flags);
    if (n < 0) {
        perror("recv error");
        exit(-1);
    }
    cout << "recieved" << endl;
    return n;
}