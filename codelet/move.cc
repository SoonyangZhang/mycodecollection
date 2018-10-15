#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

class Test
{
public:
    Test() : p(nullptr)
    {
        cout<<"constructor"<<endl;
    }

    ~Test()
    {
        cout<<"destructor"<<endl;
        delete [] p;
    }
    void Alloc(){
        p=new char [10];
    }
    uint64_t getAddr(){
        uint64_t addr=(uint64_t)p;
    }
    Test(const Test& t) : p(nullptr), str(t.str)
    {
        cout<<"copy constructor"<<endl;
        if(t.p != nullptr)
        {
            p = new char[strlen(t.p)+1];
            memcpy(p, t.p, strlen(t.p)+1);
        }

    }

    Test& operator = (const Test& t)
    {
        cout<<"operator = "<<endl;
        if( this != &t )
        {
            char *tmp =nullptr;
            if( t.p != nullptr)
            {
                tmp = new char[strlen(t.p)+1];
                memcpy(tmp, t.p, strlen(t.p)+1);
            }
            delete [] p;
            p = tmp;
            str = t.str;
        }

        return *this;
    }

    Test(Test && t)noexcept : p(t.p), str(std::move(t.str))//如何移动由string类完成
    {
        cout<<"move copy constructor"<<endl;
        t.p = nullptr;//记得，不然会对同一段内存重复delete
    }

    Test& operator = (Test &&t)noexcept
    {
        cout<<"move operator ="<<endl;
        if( this != &t)
        {
            p = t.p;
            t.p = nullptr;

            str = std::move(t.str);//如何移动由string类完成
        }

        return *this;
    }

private:
    char *p;
    std::string str;
};

int main()
{
	Test a;
	a.Alloc();
	std::cout<<"alloc "<<a.getAddr();
	Test b = std::move(a);//调用move构造函数
	std::cout<<"alloc "<<b.getAddr();
	//Test c = a;//调用copy构造函数
	return 0;
}

