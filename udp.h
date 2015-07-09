/*# coding...
watch and learn ~~*/
#ifndef UDP_H
#define UDP_H
#ifdef MYLINUX
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SOCKET int
#else
#include <WINSOCK2.H>
#endif


class myudp
{
private:
    SOCKET st;//类的内部成员一般是不暴露在类的外部

public:
    myudp();
    ~myudp();

int socket_bind(short int port);
int socket_send(const char *IP,const char *buf,int len);
int socket_recv(char *buf,int len,char *srcIP);

//明确告诉C++编译器,这是一个用C语言编译的函数,你就不用把函数名转换为C++格式了

};
#endif // UDP_H
