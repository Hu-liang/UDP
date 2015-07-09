#include <stdio.h>
#include <string.h>
#include "udp.h"



int myudp::socket_send(const char *IP,const char *buf,int len)
{
    
    //建立一个socket 第一个参数指定socket要用哪个协议 AF_NET代表要用TCP/IP协议
    //第二个岑树SOCK_DGRAM意思要用UDP协议
    //第三个参数一般默认填0
    st = socket(AF_INET,SOCK_DGRAM, 0) ;//定义一个socket
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));//初始化结构addr
    addr.sin_family = AF_INET;//代表要使用一个TCP/IP的地址
    addr.sin_port = htons(8080);//host to netshort
    addr.sin_addr.s_addr =inet_addr(IP);//给自己
    //  unsigned long laddr = inet_addr("192.168.6.200");
    //  unsigned char *p = &laddr;
    //  printf("%u,%u,%u,%u\n",*(p),*(p+1),*(p+2),*(p+3));
    
    
    size_t rc=0;
    //发送UDP数据
    rc = sendto(st,buf,len,0,(struct sockaddr *)&addr,sizeof(addr));
    
    return rc;
}

int myudp::socket_recv(char *buf,int len,char *srcIP)
{
    
    struct sockaddr_in sendaddr;
    memset(&sendaddr,0,sizeof(sendaddr));
    
#ifdef MYLINUX
    socklen_t addrlen;
#else
    int addrlen;
#endif
    addrlen = sizeof(sendaddr);
    
    
    memset(buf,0,len);
    //接受UDP数据
    size_t  rc = recvfrom(st,buf,len,0,(struct sockaddr*)&sendaddr,&addrlen);
    //inet_ntoa(sendaddr.sin_addr);//这个函数是不可重入函数
    //printf("%s:%s\n",inet_ntoa(sendaddr.sin_addr),buf);
    if(srcIP)
        strcpy(srcIP,inet_ntoa(sendaddr.sin_addr));
    
    
    return rc;
}




myudp::myudp()
{
#ifndef MYLINUX
    //初始化socket
    DWORD ver;//unsighed int
    WSADATA wsaData;
    ver =MAKEWORD(1,1);//在调用wsastartup要告诉Windows要用什么版本的socket
    WSAStartup(ver,&wsaData); //windows 要求 只要用socket 第一步必须调用这个函数
    //初始化socket完成
#endif
}


myudp::~myudp()
{
#ifdef MYLINUX
    close(st);
#else
    closesocket(st);//使用完socket要将其关闭
    WSACleanup();//释放win socket内部的相关资源
    //建立一个socket 第一个参数指定socket要用哪个协议 AF_NET代表要用TCP/IP协议
    //第二个岑树SOCK_DGRAM意思要用UDP协议
    //第三个参数一般默认填0
    st = socket(AF_INET,SOCK_DGRAM,0) ;//定义一个socket
#endif
    
}


int myudp::socket_bind(short port)
{
    
    
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));//初始化结构addr
    addr.sin_family = AF_INET;//代表要使用一个TCP/IP的地址
    addr.sin_port = htons(port);//host to netshort
    addr.sin_addr.s_addr =htonl(INADDR_ANY);//作为接收方,不需要指定具体的IP地址,接受主机是什么,我就在IP地址收什么
    int rc=0;
    return bind(st,(struct sockaddr *)&addr,sizeof(addr));//将端口号和程序绑定
}
