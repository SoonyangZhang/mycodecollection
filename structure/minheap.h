#ifndef EVENT_H
#define EVENT_H
#include<stdint.h>
#include<memory>
//copy fromm libevent
namespace ns3
{
typedef struct
{
	int fd;
	short event;
	int min_heap_idx;
	void *context;
	void(*ev_callback)(int fd,short event,void* context);
	uint32_t timeout;  //
}lib_event_t;//this is copied from libevent,and simulate a task queue for webrtc
void event_init(lib_event_t *ev,int fd,short event,uint32_t timeout,void *context);
class MinHeap
{
public:
	MinHeap();
	~MinHeap();
	int Push(lib_event_t *ev);
	lib_event_t * Pop();
	lib_event_t *Top(){return m_n?m_p[0]:0;}
	uint32_t Size(){return m_n;}
	bool IsTop(lib_event_t *ev){return ev->min_heap_idx==0;}
	bool Empty(){return m_n==0;}
	uint32_t Erase(lib_event_t *ev);
	int Reserve(uint32_t n);
private:
	uint32_t Greater(lib_event_t *lhs,lib_event_t *rhs);
	void ShiftUp(uint32_t hole_index,lib_event_t *ev);
	void ShiftUpUnconditional(uint32_t hole_index,lib_event_t *ev);
	void ShiftDown(uint32_t hole_index,lib_event_t *ev);
	lib_event_t **m_p;
	uint32_t m_n{0}; //element size of ev
	uint32_t m_a{0}; //total memory size of ev
};
}
#endif
