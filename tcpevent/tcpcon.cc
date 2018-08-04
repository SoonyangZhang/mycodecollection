/*
 * tcpcon.cc
 *
 *  Created on: 2018年8月4日
 *      Author: LENOVO
 */
#include "tcpcon.h"
#include <unistd.h>
#include <stdio.h>
#include <memory.h>
#include<errno.h>
namespace zsy{
TcpCon::TcpCon(int fd,EventLoop *loop,TcpListener *listener){
	m_fd=fd;
	m_loop=loop;
	m_listener=listener;
	setnonblocking(m_fd);
}
TcpCon::~TcpCon(){
	printf("client dtor\n");
}
void TcpCon::RegisterEvent(int mask){
	m_loop->AddEvent(this,m_fd,mask);
}
bool TcpCon::OnIncomingEvent(){
	char buffer[1500];
	memset(buffer,0,sizeof(buffer));
	int nread=0;
	nread = read(m_fd, buffer, sizeof(buffer));
	if(nread>0){
		m_total+=nread;
		printf("%d read size %d total %d\n",m_counter,nread,m_total);
		m_counter++;
		
	}
	if(nread==-1){
		printf("impossible\n");
		if(errno != EAGAIN){

		}
	}
	if(nread==0){//close by client
		printf("client close\n");
		Close();
	}
	return true;
}
void TcpCon::CloseByListener(){
	m_loop->DelEvent(this,m_fd);
	close(m_fd);
}
void TcpCon::Close(){
	m_loop->DelEvent(this,m_fd);
	m_listener->FreeSession(this);
	close(m_fd);
}
}



