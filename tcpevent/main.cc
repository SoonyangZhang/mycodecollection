/*
 * main.cc
 *
 *  Created on: 2018年8月4日
 *      Author: LENOVO
 */
#include "eventloop.h"
#include "tcplistener.h"
#include <signal.h>
#define	MAXEPOLL	100
static int m_running=1;
void signal_exit_handler(int sig)
{
	m_running=0;
}

int main()
{
	signal(SIGTERM, signal_exit_handler);
    signal(SIGINT, signal_exit_handler);
    signal(SIGTSTP, signal_exit_handler);
	char servIp[32]="127.0.0.1";
	int port =1234;
	zsy::EventLoop loop(MAXEPOLL);
	zsy::TcpListener TcpSever(&loop,servIp,port);
	while(m_running){
		loop.loop();
	}
	TcpSever.Exit();
	loop.ExitGrace();
	return 0;

}



