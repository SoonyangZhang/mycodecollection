/*
 * tcplistener.h
 *
 *  Created on: 2018年8月4日
 *      Author: LENOVO
 */

#ifndef TCPLISTENER_H_
#define TCPLISTENER_H_
#include "eventloop.h"
#include "tcp.h"
#include <list>
namespace zsy{
class Tcpcon;
class TcpListener:public TcpInterface{
public:
	TcpListener(EventLoop *loop,char*servIp,int port);
	~TcpListener() override{};
	void Exit();
	void FreeSession(TcpInterface*object);
	bool OnIncomingEvent() override;
	void OnWriteEvent() override{}
private:
	EventLoop *m_loop;
	std::list<TcpInterface*>m_sessions;
	int m_fd;
};
}



#endif /* TCPLISTENER_H_ */
