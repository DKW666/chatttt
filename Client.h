//处理用户
#include "Server.h"

#define CLIENT_NUM 30
#define NAME_NUM 13

string namelist[NAME_NUM] = {
    "任我行",
    "向问天",
    "桃叶仙",
    "风清扬",
    "丘处机",
    "王师我",
    "海大富",
    "韦一笑",
    "(*•̀ᴗ•́*)و ̑̑",
    "尹志平",
    "丁春秋",
    "MiaoPaSu～",
    "岳不群",
};
class Client{
public:
    Client():name(" "), id(0){}
    void Init(int cfd);
    void Prompt();
    int getID(){
        return this->id;
    }
    string getName(){
        return this->name;
    }
private:
    string name;
    int id; 
}; 

void Client::Init(int cfd){
    int n = rand() % NAME_NUM; 
    this->name = namelist[n];
    this->id = cfd; 
}

void Client::Prompt(){
    cout << "新连接，文件描述符/客户端编号为： " << this->id 
    << "， 昵称为： " << this->name  << this->id << endl;
}