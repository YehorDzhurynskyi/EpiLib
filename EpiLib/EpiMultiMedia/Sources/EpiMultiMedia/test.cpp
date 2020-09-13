#pragma comment(lib, "bcrypt.lib")
#pragma comment(lib, "Secur32.lib")
#pragma comment(lib, "Strmiids.lib")
#pragma comment(lib, "dxva2.lib")
#pragma comment(lib, "evr.lib")
#pragma comment(lib, "mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfplay.lib")
#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

extern "C"
{

#include "libavcodec/avcodec.h"
#include "libavfilter/avfilter.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include "libswresample/swresample.h"
#include "libswscale/swscale.h"

}

void EpiMutltimedia_print()
{
    printf("avcodec_version=%u\n", avcodec_version());
    printf("avfilter_version=%u\n", avfilter_version());
    printf("avformat_version=%u\n", avformat_version());
    printf("avdevice_version=%u\n", avdevice_version());
    printf("swresample_version=%u\n", swresample_version());
    printf("swscale_version=%u\n", swscale_version());
}
