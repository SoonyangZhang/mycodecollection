#include<stdio.h>
#include<iostream>
#include<thread>
#include<vector>
#include<unistd.h>
#include "lock.h"
#include "atomiclock.h"
using namespace std;
using namespace zsy;
int total_num=0;
AtomicLock lock_;
void Add(int){
    LockScope cs_(&lock_);
    for(int i=0;i<1000;i++){
    usleep(1000);
    total_num++;
    }

}
int main()
{
    std::vector<std::thread> threads;
    for (int i=0;i<10;i++){
        threads.push_back(std::thread(Add,i));
    }
    for (auto &h:threads){
        h.join();
    }
    printf("%d\n",total_num);
    return 0;
}
