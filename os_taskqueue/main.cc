#include <iostream>
#include<stdint.h>
#include <unistd.h>
#include "timeutils.h"
#include "taskqueue.h"
using namespace std;
using namespace rtc;
class Test
{
public:
    Test(Ns3TaskQueue*taskQueue){m_queue=taskQueue;}
    ~Test(){}
    void Increase()
    {
        m_counter++;
        printf("hello world%d\n",m_counter);
    }
    void TestClosure()
    {
        m_queue->PostTask([this]{
        this->Increase();
                          });
    }
    uint32_t GetValue(){return m_counter;}
    void TestDelay(uint32_t delay)
    {
        printf("in test %d\n",delay);
        m_queue->PostDelayedTask([this,delay]{
                 this->Increase();
                 printf("%d c %d\n",delay,this->GetValue());
                                 },delay);
    }
private:
    Ns3TaskQueue *m_queue;
    uint32_t m_counter{0};

};
int main()
{
    Ns3TaskQueue taskQueue;
    Test test(&taskQueue);
    test.TestDelay(4);
    test.TestDelay(8);
    test.TestDelay(2);
    uint32_t elapse=100;
    uint32_t now=TimeMillis();
    uint32_t stop=now+elapse;
    uint32_t gap=1;
    uint32_t last=now;
    while(now<stop)
    {
        if(now-last>=gap){
        test.TestDelay(1);
        last=now;
        }
        now=TimeMillis();
    }
    taskQueue.Stop();

}
