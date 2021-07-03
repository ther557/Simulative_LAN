#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include "List.h"

using namespace std;

LIST lan;

bool isThisIDLegal(int num);
void homePage();
void goToWhere();
void option1_add();
void option2_delete();
void option3_sendPtP();
void option4_sendPtA();
void option5_testPFM();

bool isThisIDLegal(int num)
{
    NODE *p = lan.getHead();
    while (p->next != NULL)
    {
        p=p->next;
        if (p->ID == num)
            return true;
    }
    return false;
}

void homePage()
{
    cout << "|-------------------------------------------------------|" << endl;
    cout << "|Please tell me the work you want me to do:             |" << endl;
    cout << "|(1).add node                                           |" << endl;
    cout << "|(2).delete node                                        |" << endl;
    cout << "|(3).send message to other node                         |" << endl;
    cout << "|(4).send messages to ohter nodes                       |" << endl;
    cout << "|(5).test performance by sending messages to other nodes|" << endl;
    cout << "|(0).EXIT                                               |" << endl;
    cout << "|-------------------------------------------------------|" << endl;
}

void option1_add()
{
    string sort;
    char loop = 'y';
    do
    {
        cout << "Please input the sort of node:" << endl;
        cin >> sort;
        lan.addNode(sort);
        cout << "Do you want continue adding (y/n)?" << endl;
        cin >> loop;
    } while (loop == 'y');
    lan.show();
}

void option2_delete()
{
    int id;
    char loop = 'y';
    int len = lan.gatLength();
    if (len == 0) //判断链表长度是否违法
    {
        cout << "List is empty" << endl;
        return;
    }
    do
    {
    INPUT:
        cout << "Please input the ID of node you want to delete:" << endl;
        cin >> id;
        if (!isThisIDLegal(id)){
            cout << "【Your input is wrong! Please try it again!】" << endl;
            goto INPUT;
        }
        lan.deleteNode(id);
        cout << "Do you want continue deleteing (y/n)?" << endl;
        cin >> loop;
    } while (loop == 'y');
    lan.show();
}

void option3_sendPtP()
{
    int len = lan.gatLength();
    if(len == 0){
        cout << "List is empty" << endl;
        return;
    }
INPUT_send:
    cout << "Please input the id of delever" << endl;
    int id_send;
    cin >> id_send;
    cin.get();
    if (!isThisIDLegal(id_send)){
        cout << "【Your input is wrong! Please try it again!】" << endl;
        goto INPUT_send;
    }
    string text;
    cout << "Please input the mess you want to send:" << endl;
    getline(cin, text);
INPUT_rece:
    cout << "Please input the ID of reveiver:" << endl;
    int id_rece;
    cin >> id_rece;
    if (!isThisIDLegal(id_rece)){
        cout << "【Your input is wrong! Please try it again!】" << endl;
        goto INPUT_rece;
    }
    lan.sendMess(text, id_send, id_rece);
    cout << "Your message has been delivered." << endl;
    lan.show();
}

void option4_sendPtA()
{
    int len = lan.gatLength();
    if(len == 0){
        cout << "List is empty" << endl;
        return;
    }
INPUT:
    cout << "Please input id_send" << endl;
    int id_send;
    cin >> id_send;
    cin.get();
    if (!isThisIDLegal(id_send)){
        cout << "【Your input is wrong! Please try it again!】" << endl;
        goto INPUT;
    }
    string text;
    cout << "Please input the mess you want to send:" << endl;
    getline(cin, text);
    lan.sendToAllNode(text, id_send);
    cout << "Your message has been delivered." << endl;
    lan.show();
}

void option5_testPFM()
{
    int len = lan.gatLength();
    if(len == 0){
        cout << "List is empty" << endl;
        return;
    }
    string text = "This is a message for test.";
    NODE *p = lan.getHead();
    p = p->next;
    int id_send = p->ID;
    time_t begin_t = clock();
    lan.sendToAllNode(text, id_send);
    time_t finish_t = clock();
    cout << "Message have been send to all nodes, it cost time:" << (double)(finish_t - begin_t) * 1000.0 / CLOCKS_PER_SEC << " ms" << endl;
    lan.show();
}

void goToWhere()
{
    int x = 0;
    cout << "Your choose is:";
    cin >> x;
    while (x != 0)
    {
        switch (x)
        {
        case 1:
            option1_add();
            break;
        case 2:
            option2_delete();
            break;
        case 3:
            option3_sendPtP();
            break;
        case 4:
            option4_sendPtA();
            break;
        case 5:
            option5_testPFM();
            break;
        default:
            cout << "Your input is wrong.Please try again." << endl;
            break;
        }
        homePage();
        cout << "Your choose is:";
        cin >> x;
    }
    if (x == 0)
        cout << "Thank you for using it, have a great day!" << endl;
}
#endif