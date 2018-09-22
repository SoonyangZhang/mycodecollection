/*
 * tcplistener.cc
 *
 *  Created on: 2018年8月4日
 *      Author: LENOVO
 */
#include "tcplistener.h"
#include "tcpcon.h"
#include "flag.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define	MAXBACK	1000
namespace zsy{
TcpListener::TcpListener(EventLoop *loop,char*servIp,int port){
	m_loop=loop;
	struct sockaddr_in servaddr;
	bzero( &servaddr, sizeof( servaddr ) );
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(servIp);
	servaddr.sin_port = htons(port);
	m_fd = socket( AF_INET, SOCK_STREAM, 0);
	setnonblocking(m_fd);
	if(bind(m_fd, ( struct sockaddr *)&servaddr, sizeof( struct sockaddr ))==-1){
		printf("Bind Error : %d\n", errno);
		exit( EXIT_FAILURE );
	}
	int ireuseadd_on = 1;
	setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &ireuseadd_on, sizeof(ireuseadd_on));
	if(listen(m_fd, MAXBACK)==-1)
	{
		printf("listen...%d\n" , errno );
		exit( EXIT_FAILURE );
	}
	int mask=AE_READABLE;
	m_loop->AddEvent(this,m_fd,mask);
}
void TcpListener::Exit(){
	for(auto it=m_sessions.begin();it!=m_sessions.end();){
		TcpCon *con=static_cast<TcpCon*>(*it);
		con->CloseByListener();
		delete *it;
		m_sessions.erase(it++);
	}
}
void TcpListener::FreeSession(TcpInterface*object){
	m_sessions.remove(object);
	m_loop->FreeSession(object);
}
bool TcpListener::OnIncomingEvent(){
	int newfd;
	struct sockaddr_in cliaddr;
	socklen_t	len = sizeof( struct sockaddr_in );
	if( ( newfd = accept(m_fd, (struct sockaddr *)&cliaddr, &len ) ) == -1 )
	{
		printf("Accept Error : %d\n", errno);
		exit( EXIT_FAILURE );
	}
	TcpCon *newCon=new TcpCon(newfd,m_loop,this);
	m_sessions.push_back(newCon);
	int mask=AE_READABLE;
	newCon->RegisterEvent(mask);
}
}



