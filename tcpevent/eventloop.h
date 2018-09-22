#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H
#include <sys/epoll.h>
#include<map>
#include<list>
#include "tcp.h"
namespace zsy{
class EventLoop
{
public:
	EventLoop(int maxpoll);
	~EventLoop();
	int AddEvent(void *object,int fd,int mask);
	int DelEvent(void *object,int fd);
	int ModifyEvent(void*object,int fd,int mask);
	void loop();
	void FreeSession(TcpInterface*object);
	void ExitGrace();
private:
	int m_maxpoll;
	int m_efd;
	struct epoll_event* m_events;
	std::list<TcpInterface*>m_free_sessions;
	int m_fds{0};
};
}
#endif
