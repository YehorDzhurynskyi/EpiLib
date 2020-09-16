#include "EpiMultimedia/Resource/mmResourceManager.h"

#include "EpiMultimedia/Resource/mmResourceAudio.h"

// TODO: handle it properly
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

#include "libavformat/avformat.h"

}

EPI_NAMESPACE_BEGIN()

mmResource* mmResourceManager::LoadResource(const epiChar* url, epiBool loadFully)
{
    std::unique_ptr<mmResource>& resource = m_Resources[url];
    resource = std::make_unique<mmResource>();
    resource->SetURI(url); // TODO: replace with URI but not URL

    // TODO: investigate `options` parameter
    AVFormatContext* avFormatContext = nullptr;
    if (const int ret = avformat_open_input(&avFormatContext, url, nullptr, nullptr); ret == 0)
    {
        // TODO: investigate
        // avFormatContext->metadata;

        // TODO: investigate `options` parameter
        if (const int ret = avformat_find_stream_info(avFormatContext, nullptr); ret >= 0)
        {
            resource = std::make_unique<mmResourceAudio>();
            resource->SetURI(url); // TODO: replace with URI but not URL
            resource->SetMIME(mmMIMEType::AUDIO_MPEG); // TODO: determine MIME type
            resource->SetStatus(mmResourceStatus::LoadedPartially);

            // TODO: figure out whether `avformat_close_input` should be called on `avformat_...` failure
            avformat_close_input(&avFormatContext);
        }
        else
        {
            // TODO: log
        }
    }
    else
    {
        // TODO: log
    }

    return resource.get();
}

EPI_NAMESPACE_END()
