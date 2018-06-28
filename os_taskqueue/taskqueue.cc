/*
 * ns3taskqueue.cc
 *
 *  Created on: 2018.6.19
 *      Author: zsy
 *      email 865678017@qq.com
 */
#include "taskqueue.h"
#include "timeutils.h"
namespace rtc
{
Ns3TaskQueue::Ns3TaskQueue():thread_(&Ns3TaskQueue::ThreadMain,this,"taskqueue")
{
    Start();
}
bool Ns3TaskQueue::IsCurrent() const{return true;}
void Ns3TaskQueue::Start()
{
    m_running=true;
    thread_.Start();
}
void Ns3TaskQueue::Stop()
{
    m_running=false;
    thread_.Stop();
}
void Ns3TaskQueue::Process()
{

	while(m_running)
	{
        rtc::CritScope lock(&pending_lock_);
	    while(!m_pending.empty())
	    {
	        std::unique_ptr<QueuedTask> task=std::move(m_pending.front());//move ownership
	        m_pending.pop_front();
	        task->Run();
	        //task.release();// this will cause memory leakgy
	    }
	    uint64_t time_ms=TimeMillis();
	    for(auto it=m_delayTasks.begin();it!=m_delayTasks.end();)
	    {
	    	if(it->first<=time_ms)
	    	{
	    		std::unique_ptr<QueuedTask> task=std::move(it->second);
	    		task->Run();
	    		m_delayTasks.erase(it++);
	    	}else{
	    		break;
	    	}
	    }
	}
}
void Ns3TaskQueue::PostTask(std::unique_ptr<QueuedTask>task)
{
    rtc::CritScope lock(&pending_lock_);
	m_pending.push_back(std::move(task));
}
void Ns3TaskQueue::PostDelayedTask(std::unique_ptr<QueuedTask> task, uint32_t time_ms)
{

    uint64_t now=TimeMillis();
    uint64_t future=now+time_ms;
    rtc::CritScope lock(&pending_lock_);
    m_delayTasks.insert(std::make_pair(future,std::move(task)));
}
void Ns3TaskQueue::ThreadMain(void* context)
{
    Ns3TaskQueue *task=static_cast<Ns3TaskQueue*>(context);
    task->Process();
}
}
