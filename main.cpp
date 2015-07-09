#include <iostream>
#include "udp.h"
#include <string.h>


using namespace std;

int main(int argc,char *args[])
{
    if(argc >1)
    {
        myudp udp;
        char buf[1024]={0};
        while(1)
        {
            memset(buf,0,sizeof(buf));
            gets(buf);
            udp.socket_send(args[1],buf,strlen(buf));
            if(strncmp(buf,"exit",4)==0)
                break;
        }
    }
    else
    {
        myudp udp;
        char buf[1024]={0};
        if(udp.socket_bind(8080) > -1)
        {
            char ip[100] = {0};
            while(1)
            {
                memset(buf,0,sizeof(buf));
                memset(ip,0,sizeof(ip));
                udp.socket_recv(buf,sizeof(buf),ip);
                if(strncmp(buf,"exit",4)==0)
                    break;
                cout <<ip <<":" ;
                cout <<buf <<endl;
                
            }
        }
    }
    
    return 0;
}
