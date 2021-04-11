#include "Controller.h"

void Controller::Start(){
    //调用socket类的初始化函数
    socketfd = socket.Initialize();

    //调用epoll初始化函数
    epollfd = epoll.Initialize(socketfd);

    //初始化就绪事件数
    ep_events_count = 0;

    //总之设为0就完事了
    clients_count = 0;  

    //开始聊天
    Chatting(); 
}

//结束辽
void Controller::End(){
    //关闭socket
    close(socketfd);
    
    //关闭epoll监听
    close(epollfd);
}

//添加新客户端
void Controller::Add_client(){
    //socket接收客户端 
    int clientfd = socket.Accept_client(); 

    //epoll添加新监听事件
    epoll.Add_epoll_wait(clientfd); 

    //初始化新的客户端对象
    clients[clients_count].Init(clientfd);
    
    //添加新客户端于list中
    clients_list.push_back(&clients[clients_count]);

    //提示新加入
    Prompt();  

    //客户端已连接数++ 
    clients_count++;
}

//提示新客户端连接
void Controller::Prompt(){
    //通知服务端
    clients_list.back()->Prompt();

    //预先准备好缓冲区
    /*
    调用socket的方法（update（））来准备@所有人
    */
}

//接收消息
void Controller::Receive_message(int evtfd){
    //遍历list找到那个发消息的昵称
    string nameTemp;
    for (Client *clie : clients_list){
        if(clie->getID() == evtfd)
            string nameTemp = clie->getName();
    }

    //套接字接收消息
    int n = (socket.Receive_client(evtfd));

    //如果什么内容都没有读取到
    if (n == 0) {
        //从保存客户端的list中删除这个人
        for (Client *clie : clients_list){
            if (clie->getID() == evtfd)
                clients_list.remove(clie);  
        }
        /*
        之后在这里加上功能代码
        公屏喷这个逃跑的
        */

       //人数-1
       clients_count--; 

       //关闭epoll监听?
       close(evtfd);
    }

    //预先准备好发信缓冲区
    socket.Update_buffer(evtfd, nameTemp);
}

//广播消息
void Controller::Boardcast(int evtfd){
    //直接就是个大锅炒
    for (Client *clie : clients_list) 
        socket.Send_clients(evtfd);
} 

void Controller::Chatting(){
    //客户端监听得来的数据打到公屏！！！
    //这可咋实现啊 QAQ？？？
    //冲！

    //设置epoll监听事件数量
    struct epoll_event events[EPOLL_SIZE]; 

    //主循环 
    while(true){ 
        //获取就绪事件
        int ready_evts_count = epoll.Wait_evt(events);

        //处理每个就绪事件
        for(int i = 0; i < ready_evts_count; i++){
            //判断epoll监听的句柄是不是socket的句柄！！！
            int evtfd = events[i].data.fd;
            if(evtfd == socketfd)
                Add_client();  //添加新用户
            else 
                Receive_message(evtfd);//接收消息
            //广播新收到的信息 
            Boardcast(evtfd); 
        }
    }
}       
