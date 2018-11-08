#include "videotrace.h"
#include <assert.h>
#include <iostream>
#include <string.h>
namespace ck{
FRAMETYPE GetFrameType(char *str){
    if(strcmp(str,"H")==0){
        return FRAMETYPE::H;
    }
    if(strcmp(str,"P")==0){
        return FRAMETYPE::P;
    }
    if(strcmp(str,"B")==0){
    return FRAMETYPE::B;
    }
    return FRAMETYPE::V;
}
VideoTrace::VideoTrace(std::string &name)
:fp_(NULL)
,fid_(0)
,ftype_(0)
,flen_(0)
,shit_(0){
    fp_=fopen(name.c_str(),"r");
    assert(fp_);
}
VideoTrace::~VideoTrace(){
    if(fp_){
        fclose(fp_);
    }
}
void VideoTrace::PrintNext(){
    uint32_t id;
    char type[2];
    int length=0;
    int shit=0;
    char time [20]={0};
    if(!feof(fp_)){
        fscanf(fp_,"%d%s%d%d%s",&id,type,&length,&shit,time);
    }
    fid_=id;
    ftype_=GetFrameType(type);
    shit_=shit;
    time_=std::string(time);
    flen_=length;
}
}
