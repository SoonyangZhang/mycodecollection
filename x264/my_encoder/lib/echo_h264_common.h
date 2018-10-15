/*-
* Copyright (c) 2017-2018 wenba, Inc.
*	All rights reserved.
*
* See the file LICENSE for redistribution information.
*/

#ifndef __echo_h264_common_h___
#define __echo_h264_common_h___

/*�����ֱ���ֵ*/
#define PIC_WIDTH_160	160
#define PIC_HEIGHT_120	120

#define PIC_WIDTH_320	320
#define PIC_HEIGHT_240	240

#define PIC_WIDTH_480	480
#define PIC_HEIGHT_360	360

#define PIC_WIDTH_640	640
#define PIC_HEIGHT_480	480

#define PIC_WIDTH_960	960
#define PIC_HEIGHT_640	640

#define PIC_WIDTH_1280	1280
#define PIC_HEIGHT_720	720

#define PIC_WIDTH_1920	1920
#define PIC_HEIGHT_1080 1080

enum Resolution
{
	VIDEO_120P,
	VIDEO_240P,
	VIDEO_360P,
	VIDEO_480P,
	VIDEO_640P,
	VIDEO_720P,
	VIDEO_1080P,
};

#define RESOLUTIONS_NUMBER 7

#define DEFAULT_FRAME_RATE 16

/*480P�����ʷ�Χ����ʼ����*/
#define MAX_VIDEO_BITRAE (1000 * 1000)
#define MIN_VIDEO_BITARE (48 * 1000)
#define START_VIDEO_BITRATE (800 * 1000) 

/*480P�����ʷ�Χ����ʼ����*/
#define MAX_320_VIDEO_BITRAE (160 * 1000)
#define MIN_320_VIDEO_BITARE (100 * 1000)
#define START_320_VIDEO_BITRATE (120 * 1000) 

//codec payload type,���ﲢû����ffmpeg��codec ID,��Ҫ�ǿ���ffmpeg��codec ID��32λ������ʾ��������Э�鴫����̲���Ҫ��ô��������
enum
{
	codec_raw = 32,
	codec_h263,
	codec_mpeg4,
	codec_h264,
	codec_h265,
	
	codec_vp8,
	codec_vp9
};

#endif
