#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "List.h"

using namespace std;

//随机数产生的范围
#define rangeMIN 10000
#define rangeMAX 99999

//默认构造函数
LIST::LIST()
{
    head = new NODE;
    tail = new NODE;
    head->next = tail;
    head->prev = NULL;
    head->sort = "-1";
    head->ID = -1;
    tail->prev = head;
    tail->next = NULL;
    tail->sort = "-1";
    tail->ID = -1;
    length = 0;
}

//析构函数
LIST::~LIST()
{
    if (length == 0)
    {
        delete head;
        delete tail;
        head = NULL;
        tail = NULL;
        return;
    }
    while (head->next != NULL)
    {
        NODE *temp = head;
        head = head->next;
        delete temp;
    }
    delete head;
    head = NULL;
}

//添加节点（尾插法）
void LIST::addNode(string sort1)
{
    NODE *temp = this->tail;
    tail->sort = sort1;
    srand((unsigned)time(0));
    tail->ID = (rand() % (rangeMAX - rangeMIN + 1)) + rangeMIN; //为链表中每个节点分配一个ID，方便消息收发时寻址
    tail->next = new NODE;
    NODE *p = tail;
    tail = tail->next;
    tail->prev = p;
    tail->next = NULL;
    length++;
}

//删除节点
void LIST::deleteNode(int index)
{
    NODE *p = head;
    while (p->next != NULL)
    {
        p = p->next;
        if (p->ID == index)
        {
            NODE *temp = p->prev;
            temp->next = p->next;
            p->next->prev = temp;
            delete p;
            length--;
            return;
        }
    }
}

//以文字形式展示节点
void LIST::show()
{
    if (length == 0)
    {
        cout << "List is empty" << endl;
        return;
    }
    cout << "*************************************" << endl;
    NODE *p = head->next;
    //展示出节点种类、ID、和当前收到的消息，没有消息则不显示
    while (p->next != NULL)
    {
        cout << "Node[" << p->sort << "-" << p->ID << "]" << p->text << endl;
        p = p->next;
    }
    cout << "*************************************" << endl;
}

//以图像形式展示节点（演示用）
void LIST::showNodeInGra()
{
    cout << "Waiting...";
}

//发送消息
void LIST::sendMess(string mess, int id_send, int id_rece)
{
    NODE *pRece = getAddress(id_rece);
    //将消息直接写入目标节点收件箱，既然是模拟，就省去了发送的过程。
    //在写入的过程中将发件人的ID一起写入，并用[]包裹起来方便辨认
    pRece->text = mess + '[' + to_string(id_send) + ']';
    //cout<<pRece->text<<endl;
}

//发送消息至所有节点
void LIST::sendToAllNode(string mess, int id_send)
{
    NODE *p = head->next;
    while (p->next != NULL)
    {
        if (p->ID == id_send)
        {
            p = p->next;
            continue;
        }
        p->text = mess + '[' + to_string(id_send) + ']';
        p = p->next;
    }
}