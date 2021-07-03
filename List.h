#ifndef LIST_H
#define LIST_H

#include <string>
#include <iostream>

using std::string;

class NODE{
public:
    NODE *prev;
    NODE *next;
    int ID;//随机生成一个五位数字组成的序号
    string sort;//存入节点种类的名称，如PC、smart phone等
    string text;//用来存放收到的消息
};

class LIST{
    NODE *head;
    NODE *tail;
    int length;//链表长度
    NODE *getAddress(int index){//发送消息时获取目标节点地址
        NODE *p=head;
        while(p->next!=NULL){
            p=p->next;
            if(p->ID==index) break;
        }
        return p;
    }
public:
    LIST();
    ~LIST();
    void addNode(string sort1);//添加节点
    void deleteNode(int index);//删除节点
    void show();//展示节点
    void showNodeInGra();//以图像形式展示节点
    void sendMess(string mess,int id_send, int id_rece);//发送消息
    void sendToAllNode(string mess,int id_send);//向全体局域网广播
    NODE *getHead(){//获取头指针
        return head;
    }
    int gatLength(){
        return length;
    }
};

#endif