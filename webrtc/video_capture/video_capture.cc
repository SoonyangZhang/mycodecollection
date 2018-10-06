/*
 * video_capture.cc
 *
 *  Created on: 2018.6.22
 *      Author: zsy
 *      email 865678017@qq.com
 *      This file is modified from video_capture_unittest.cc
 * https://cs.chromium.org/chromium/src/third_party/webrtc/
 */

#include "api/video/i420_buffer.h"
#include "api/video/video_frame.h"
#include "common_video/libyuv/include/webrtc_libyuv.h"
#include "modules/utility/include/process_thread.h"
#include "modules/video_capture/video_capture.h"
#include "modules/video_capture/video_capture_factory.h"
#include "rtc_base/criticalsection.h"
#include "rtc_base/scoped_ref_ptr.h"
#include "rtc_base/timeutils.h"
#include "system_wrappers/include/sleep.h"
#include <stdint.h>
#include <iostream>
#include <signal.h>
using namespace webrtc;
using namespace std;
static const int kTestHeight = 720;//1080;//288;
static const int kTestWidth = 1280;//1920;//352;
static const int kTestFramerate = 30;
namespace zsy
{
class VideoCaptureCallback:
		public rtc::VideoSinkInterface<webrtc::VideoFrame> {

public:
	void OnFrame(const webrtc::VideoFrame& videoFrame) override {
	    int height = videoFrame.height();
	    int width = videoFrame.width();
	    uint32_t size=videoFrame.size();
	    uint64_t now_ms=rtc::Time();
	    uint64_t record_ms=0;
	    if(last_time_==0){
	    	record_ms=0;
	    }else
	    {
	    	record_ms=now_ms-last_time_;
	    }
	    std::cout<<frame_num_<<" "<<record_ms<<" "<<size<<" "<<height<<" "<<width<<std::endl;
	    last_time_=now_ms;
	    frame_num_++;
	}
private:
	int frame_num_{0};
	uint64_t last_time_{0};
};
class VideoCapture{
public:
 VideoCapture() : number_of_devices_(0) {}
 void SetUp() {
   device_info_.reset(webrtc::VideoCaptureFactory::CreateDeviceInfo());
   assert(device_info_.get());
   number_of_devices_ = device_info_->NumberOfDevices();
   assert(number_of_devices_>0u);
 }
 void OpenVideoCaptureDevice()
 {
	    char device_name[256];
	    char unique_name[256];
	    capture_module_=VideoCaptureFactory::Create(unique_name);
	    capture_module_->RegisterCaptureDataCallback(&capture_callback_);
 }
 void GetCapability(webrtc::VideoCaptureCapability &capability)
 {
	 device_info_->GetCapability(capture_module_->CurrentDeviceName(), 0, capability);
 }
 void StartCapture(webrtc::VideoCaptureCapability capability)
 {
	 capture_module_->StartCapture(capability);
 }
 void StopCapture()
{
   capture_module_->StopCapture();
}
private:
 uint32_t number_of_devices_;
 std::unique_ptr<webrtc::VideoCaptureModule::DeviceInfo> device_info_;
 VideoCaptureCallback capture_callback_;
 rtc::scoped_refptr<webrtc::VideoCaptureModule> capture_module_;
};
}
bool m_running=true;
void signal_exit_handler(int sig)
{
	m_running=false;
} 
int main()
{
	signal(SIGTERM, signal_exit_handler);
    	signal(SIGINT, signal_exit_handler);
    	signal(SIGTSTP, signal_exit_handler); 
	zsy::VideoCapture video_capture_;
	video_capture_.SetUp() ;
	video_capture_.OpenVideoCaptureDevice();
	webrtc::VideoCaptureCapability capability;
	video_capture_.GetCapability(capability);
    	capability.width = kTestWidth;
    	capability.height = kTestHeight;
   	 capability.maxFPS = kTestFramerate;
	video_capture_.StartCapture(capability);
	while(m_running)
	{
		
	}
	printf("stop capture\n");
	video_capture_.StopCapture();
	return 0;
}



