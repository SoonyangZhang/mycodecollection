#ifndef __VIDEO_TRACE_H_
#define __VIDEO_TRACE_H_
#include <stdio.h>
#include <string>
#include <stdint.h>
namespace ck{
enum FRAMETYPE{
    V,
    H,
    P,
    B,
    };
FRAMETYPE GetFrameType(char *str);
class VideoTrace{
public:
    VideoTrace(std::string &name);
    ~VideoTrace();
    void PrintNext();
private:
    FILE *fp_;
    uint32_t fid_;
    uint8_t ftype_;
    uint32_t flen_;
    uint32_t shit_;
    std::string time_;
    };
}
#endif
