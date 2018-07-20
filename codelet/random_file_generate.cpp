#include <iostream>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
    const char name[]="data7-19time21-11.bin";
    int file_size=1024*1024;
    char random[1024];
    srand(234567891);
    int i=0,j=0;
    int value=0;

    std::ofstream fout(name, std::ios::binary);
    for(j=0;j<file_size;j++)
    {
        char *p=random;
        for(i=0;i<sizeof(random)/sizeof(int);i++)
        {
        value=rand();
        memcpy(p+i*sizeof(int),&value,sizeof(int));
        }
        fout.write(random,sizeof(random));
    }

    fout.close();
    return 0;
}
