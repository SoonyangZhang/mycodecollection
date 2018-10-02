#include "event.h"
namespace ns3
{
void event_init(lib_event_t *ev,int fd,short event,uint32_t timeout,void *context)
{
    ev->fd=fd;
    ev->event=event;
    ev->timeout=timeout;
    ev->context=context;
}
MinHeap::MinHeap()
{
	m_p=nullptr;
}
MinHeap::~MinHeap()
{
	if(m_p)
	{
		free(m_p);
	}
	m_p=nullptr;
}
int MinHeap::Push(lib_event_t *ev)
{
	if(Reserve(m_n+1))
	{
		return -1;
	}
	ShiftUp(m_n++,ev);
	return 0;
}
int MinHeap::Reserve(uint32_t n)
{
	if(m_a<n)
	{
		lib_event_t **p=nullptr;
		uint32_t a=m_a?2*m_a:8;
		p=(lib_event_t**)realloc(m_p,a*sizeof(*p));
		if(!p){return -1;}
		m_p=p;
		m_a=a;
	}
	return 0;
}
uint32_t MinHeap::Greater(lib_event_t *lhs,lib_event_t *rhs)
{
	if(lhs->timeout>rhs->timeout) {return 1;}
	else {return 0;}
}
void MinHeap::ShiftUp(uint32_t hole_index,lib_event_t *ev)
{
	uint32_t parent=(hole_index-1)/2;
	while(hole_index&&Greater(m_p[parent],ev))
	{
		(m_p[hole_index]=m_p[parent])->min_heap_idx=hole_index;
		hole_index=parent;
		parent=(hole_index-1)/2;
	}
	(m_p[hole_index]=ev)->min_heap_idx=hole_index;
}
lib_event_t * MinHeap::Pop()
{
	lib_event_t *ev=nullptr;
	if(m_n)
	{
		ev=*m_p;
		ShiftDown(0,m_p[--m_n]);
		ev->min_heap_idx=-1;
	}
	return ev;
}
void MinHeap::ShiftDown(uint32_t hole_index,lib_event_t *ev)
{
	uint32_t min_child=(hole_index+1)*2;
	while(min_child<=m_n)
	{
		min_child-=min_child==m_n||Greater(m_p[min_child],m_p[min_child-1]);
		if(!Greater(ev,m_p[min_child])) break;
		(m_p[hole_index]=m_p[min_child])->min_heap_idx=hole_index;
		hole_index=min_child;
		min_child=(hole_index+1)*2;
	}
	(m_p[hole_index]=ev)->min_heap_idx=hole_index;
}
uint32_t MinHeap::Erase(lib_event_t *ev)
{
	if(-1!=ev->min_heap_idx)
	{
		lib_event_t *last=m_p[--m_n];
		uint32_t parent=(last->min_heap_idx-1)/2;
		if(ev->min_heap_idx>0&Greater(m_p[parent],last))
		{
			ShiftUpUnconditional(ev->min_heap_idx,last);
		}else{
			ShiftDown(ev->min_heap_idx,last);
		}
		ev->min_heap_idx=-1;
		return 0;
	}
	return -1;
}
void MinHeap::ShiftUpUnconditional(uint32_t hole_index,lib_event_t *ev)
{
	uint32_t parent=(hole_index-1)/2;
	do{
		(m_p[hole_index]=m_p[parent])->min_heap_idx=hole_index;
		hole_index=parent;
		parent=(hole_index-1)/2;
	}while(hole_index&&Greater(m_p[parent],ev));
	(m_p[hole_index]=ev)->min_heap_idx=hole_index;
}
}