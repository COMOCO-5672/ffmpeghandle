#pragma comment(lib, "shell32.lib")

extern "C" {
#include "libavutil/avstring.h"
#include "libavutil/eval.h"
#include "libavutil/mathematics.h"
#include "libavutil/pixdesc.h"
#include "libavutil/imgutils.h"
#include "libavutil/dict.h"
#include "libavutil/parseutils.h"
#include "libavutil/samplefmt.h"
#include "libavutil/avassert.h"
#include "libavutil/time.h"
#include "libavutil/bprint.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswscale/swscale.h"
#include "libavutil/opt.h"
#include "libavcodec/avfft.h"
#include "libswresample/swresample.h"
}


int main()
{
    avdevice_register_all();
    avformat_network_init();


    // check qsv support
    AVCodecContext *ctx { nullptr };
    AVCodec *codec { nullptr };
    AVBufferRef *device_ref { nullptr };

    int ret;

    ret = av_hwdevice_ctx_create(&device_ref
        , AV_HWDEVICE_TYPE_QSV
        , nullptr
        , nullptr
        , 0);

    if (ret < 0) {
        printf("hw_device create failed");
        return -1;
    }

    codec = avcodec_find_encoder_by_name("hevc_qsv");
    if (!codec) {
        printf("encoder no found");
        return -1;
    }

    ctx = avcodec_alloc_context3(codec);
    if (!ctx) {
        printf("alloc failed");
        return -1;
    }

    ctx->hw_device_ctx = av_buffer_ref(device_ref);
    ret = avcodec_open2(ctx, codec, nullptr);
    if (ret < 0) {
        printf("codec open failed");
        return -1;
    }

    return 0;
}
