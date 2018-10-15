/*
*http://lazybing.github.io/blog/2017/06/16/x264-to-convert-yuv-to-264/
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <x264.h>

#define FAIL_IF_ERROR(cond, ...) \
do\
{\
    if(cond)\
    {\
        fprintf(stderr, __VA_ARGS__);\
        goto fail;\
    }\
}while(0)

int main(int argc, char **argv)
{
    int width, height;
    x264_param_t param;
    x264_picture_t pic;
    x264_picture_t pic_out;
    x264_t *h;
    int i_frame = 0;
    int i_frame_size;
    x264_nal_t *nal;
    int i_nal;

    FILE *fp_src;
    FILE *fp_dst;

    FAIL_IF_ERROR(!(argc > 1), "x264_encoder usage:x264_encoder widthxheight <input.yuv> output.264\n");
    FAIL_IF_ERROR(2 != sscanf(argv[1], "%dx%d", &width, &height), "resolution not sepcified or incorrect\n");

    fp_src = fopen(argv[2], "rb");
    if(!fp_src){
        fprintf(stderr, "open input yuv file faile\n");
    }

    fp_dst = fopen(argv[3], "wb");
    if(!fp_src){
        fprintf(stderr, "open output h264 file faile\n");
    }

    //Get default params for preset/tunnig
    if(x264_param_default_preset(&param, "medium", NULL) < 0)
        goto fail;

    //Configure non-default params
    param.i_csp = X264_CSP_I420;
    param.i_width = width;
    param.i_height = height;
    param.b_vfr_input = 0;
    param.b_repeat_headers = 1;
    param.b_annexb = 1;

    //Apply profile restrictions.
    if(x264_param_apply_profile(&param, "high") < 0)
        goto fail;

    if(x264_picture_alloc(&pic, param.i_csp, param.i_width, param.i_height) < 0)
        goto fail;
#undef fail
#define fail fail2

    h = x264_encoder_open(&param);
    if(!h)
        goto fail;
#undef fail
#define fail fail3

    int luma_size = width*height;
    int chroma_size = luma_size >> 2;
    //Encode frames
    for(;;i_frame++)
    {
        //Read input frame
        if(fread(pic.img.plane[0], 1, luma_size, fp_src)!=luma_size)
            break;
        if(fread(pic.img.plane[1], 1, chroma_size, fp_src)!=chroma_size)
            break;
        if(fread(pic.img.plane[2], 1, chroma_size, fp_src)!=chroma_size)
            break;

        pic.i_pts = i_frame;
        i_frame_size = x264_encoder_encode(h, &nal, &i_nal, &pic, &pic_out);
        if(i_frame_size < 0)
            goto fail;
        else if(i_frame_size)
        {
            if(!fwrite(nal->p_payload, i_frame_size, 1, fp_dst))
                goto fail;
        }
    }

    //Flush delayed frames
    while(x264_encoder_delayed_frames(h))
    {
        i_frame_size = x264_encoder_encode(h, &nal,&i_nal, NULL, &pic_out);
        if(i_frame_size < 0)
            goto fail;
        else if(i_frame_size)
        {
            if(!fwrite(nal->p_payload, i_frame_size, 1, fp_dst))
                goto fail;
        }
    }
    x264_encoder_close(h);
    x264_picture_clean(&pic);
    fclose(fp_dst);
    fclose(fp_src);
    return 0;
#undef fail

fail3:
    x264_encoder_close(h);
fail2:
    x264_picture_clean(&pic);
fail:
    return -1;
}