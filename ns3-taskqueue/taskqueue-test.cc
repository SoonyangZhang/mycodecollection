#include "ns3/ns3taskqueue.h"
#include "ns3/log.h"
#include "ns3/core-module.h"
NS_LOG_COMPONENT_DEFINE ("TaskQueueTest");
static const uint64_t  simDuration=20;//ms
using namespace ns3;

class Test
{
public:
    Test(Ns3TaskQueue*taskQueue){m_queue=taskQueue;}
    ~Test(){}
    void Increase()
    {
		uint64_t time_ms=Simulator::Now().GetMilliSeconds();
		m_counter++;
        NS_LOG_INFO(time_ms<<" hello world "<<m_counter);
    }
    void TestClosure()
    {
        m_queue->PostTask([this]{
        this->Increase();
                          });
    }
    void TestDelay(uint32_t delay)
    {
        m_queue->PostDelayedTask([this]{
                 this->Increase();
                                 },delay);
    }
private:
    Ns3TaskQueue *m_queue;
    uint32_t m_counter{0};

};
int main()
{
	LogComponentEnable("TaskQueueTest", LOG_LEVEL_ALL);
	Ns3TaskQueue taskQueue;
    Test test(&taskQueue);
    test.TestClosure();
    test.TestClosure();
    test.TestDelay(4);
    test.TestDelay(8);
    test.TestDelay(2);
	Simulator::Stop (MilliSeconds(simDuration));
	Simulator::Run ();
	Simulator::Destroy();
	return 0;
}
