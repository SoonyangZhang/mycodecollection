/*
 * eventloop.cc
 *
 *  Created on: 2018年8月4日
 *      Author: LENOVO
 */
#include "eventloop.h"
#include "flag.h"
#include "tcp.h"
#include <malloc.h>
#include <memory.h>
#include <unistd.h>
namespace zsy
{
EventLoop::EventLoop(int maxpoll)
{
	m_events=(struct epoll_event*)malloc(maxpoll*sizeof(struct epoll_event));
	m_efd=epoll_create(maxpoll);
}
EventLoop::~EventLoop(){}
void EventLoop::loop(){
	int fds=m_fds;
	int retval=0;
	int i=0;
	for(auto it=m_free_sessions.begin();it!=m_free_sessions.end();)
	{
		delete *it;
		m_free_sessions.erase(it++);
	}
	retval=epoll_wait(m_efd,m_events,fds,-1);
	if(retval>0)
	{
		for(i=0;i<retval;i++)
		{
			TcpInterface *tcp=static_cast<TcpInterface*>(m_events[i].data.ptr);
			if(m_events[i].events&EPOLLIN)
			{

				tcp->OnIncomingEvent();
			}
			if(m_events[i].events&EPOLLOUT)
			{
				tcp->OnWriteEvent();
			}
		}
	}
}
void EventLoop::FreeSession(TcpInterface*object)
{
	m_free_sessions.push_back(object);
}
void EventLoop::ExitGrace(){
	for(auto it=m_free_sessions.begin();it!=m_free_sessions.end();)
	{
		delete *it;
		m_free_sessions.erase(it++);
	}
	close(m_efd);
}
int EventLoop::AddEvent(void *object,int fd,int mask){
	struct epoll_event ee;
	ee.events = 0;
    if (mask & AE_READABLE) ee.events |= EPOLLIN;
    if (mask & AE_WRITABLE) ee.events |= EPOLLOUT;
    ee.data.u64 = 0;
    ee.data.ptr=object;
    if( epoll_ctl(m_efd, EPOLL_CTL_ADD, fd, &ee ) < 0){
    	return -1;
    }
	m_fds++;
    return 0;
}
int EventLoop::DelEvent(void *object,int fd){
	struct epoll_event ee;
	ee.events = 0;
    ee.data.u64 = 0;
    ee.data.ptr=object;
	epoll_ctl( m_efd, EPOLL_CTL_DEL,fd, &ee );
	m_fds--;
	return 0;
}
int  EventLoop::ModifyEvent(void*object,int fd,int mask){
	struct epoll_event ee;
	ee.events = 0;
    if (mask & AE_READABLE) ee.events |= EPOLLIN;
    if (mask & AE_WRITABLE) ee.events |= EPOLLOUT;
    ee.data.u64 = 0;
    ee.data.ptr=object;
    if( epoll_ctl(m_efd, EPOLL_CTL_MOD, fd, &ee ) < 0){
    	return -1;
    }
    return 0;
}
}




