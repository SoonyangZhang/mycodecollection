/*
 * tcpcon.h
 *
 *  Created on: 2018年8月4日
 *      Author: LENOVO
 */

#ifndef TCPCON_H_
#define TCPCON_H_
#include "tcp.h"
#include "eventloop.h"
#include "tcplistener.h"
namespace zsy{
class TcpCon:public TcpInterface
{
public:
	TcpCon(int fd,EventLoop *loop,TcpListener *listener);
    ~TcpCon() override;
	void RegisterEvent(int mask);
	bool OnIncomingEvent() override;
	void OnWriteEvent() override{}
	void CloseByListener();
	void Close();
private:
	int m_fd;
	EventLoop *m_loop;
	TcpListener *m_listener;
	int m_counter{0};
	int m_total{0};
};
}



#endif /* TCPCON_H_ */
