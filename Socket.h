#ifndef SOCKET_H
#define SOCKET_H
#include "Server.h"

class Socket {
public:
    //初始化
    int Initialize(); 
    
    //接收socket
    int Accept_client();

    //从客户端读取信息
    int Receive_client(int cfd);

    //向客户端发送
    void Send_clients(int cfd);

    //更新缓冲区
    void Update_buffer(int fd, string name);

private:
    //socket文件描述符
    int socketfd;

    // 服务器端serverAddr信息
    struct sockaddr_in serverAddr;

    //缓冲区存放字符集
    char buffer[BUF_SIZE];
};
#endif