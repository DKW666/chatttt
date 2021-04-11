#include "Socket.h"
#include "wrap.cc"

int Socket::Initialize(){
    //初始化socket
    socketfd = Create_socket(PF_INET, SOCK_STREAM, 0);

    //初始化端口和IP地址
    serverAddr.sin_family = PF_INET; 
    serverAddr.sin_port = htons(SERVER_PORT); 
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP); 

    //绑定文件描述符与地址&端口
    Bind_socket(socketfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    //开始监听 
    Listen_socket(socketfd, BACKLOG); 

    //返回句柄
    return socketfd;
}

//accept sockets from clients
int Socket::Accept_client(){
    struct sockaddr_in client_address; 
    socklen_t client_addrLength = sizeof(struct sockaddr_in); 
    int clientfd = Accept_socket(socketfd, (struct sockaddr* )&client_address, &client_addrLength);
    return clientfd; 

    //测试
    cout << "client connection from: "
                     << inet_ntoa(client_address.sin_addr) << ":"
                     << ntohs(client_address.sin_port) << ", clientfd = "
                     << clientfd << endl;
}

int Socket::Receive_client(int cfd){
    bzero(buffer, BUF_SIZE);

    //int recv( _In_ SOCKET s, _Out_ char *buf, _In_ int len, _In_ int flags)
    int length = Receive_buffer(cfd, buffer, BUF_SIZE, MSG_WAITALL);

    return length;
}

void Socket::Update_buffer(int fd, string name){
    //初始化一个新的字符集来准备要发送的消息 
    char format_message[BUF_SIZE]; 

    //string convert to char *
    const char *cname = name.data();

    //formatmessage = printf("servermessage", cname,...)
    sprintf(format_message, SERVER_MESSAGE, cname, fd, buffer);

    //buffer只是在这里被改变
    memcpy(buffer,format_message,BUF_SIZE);
}

//发送数据
void Socket::Send_clients(int cfd){
    //send() 比 write()性能强 
    int n = Send_buffer(cfd, buffer, BUF_SIZE, MSG_WAITALL);
}