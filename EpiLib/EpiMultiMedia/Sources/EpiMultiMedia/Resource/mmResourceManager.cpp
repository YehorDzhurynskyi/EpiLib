#include "EpiMultimedia/Resource/mmResourceManager.h"

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

#include "EpiMultimedia/mmAudio.h"

extern "C"
{

#include "libavformat/avformat.h"

}

EPI_NAMESPACE_BEGIN()

mmResource* mmResourceManager::LoadResource(const epiChar* url, bool deepLoad)
{
    std::unique_ptr<mmResource>& resource = m_Resources[url];
    resource = std::make_unique<mmResource>();
    resource->SetURL(url);
    resource->SetStatus(mmResourceStatus::Empty);

    if (deepLoad)
    {
        LoadResourceDeep(*resource);
    }
    else
    {
        LoadResourceShallow(*resource);
    }

    return resource.get();
}

void mmResourceManager::LoadResourceShallow(mmResource& resource)
{
    if (auto status = resource.GetStatus();
        status != mmResourceStatus::Empty &&
        status != mmResourceStatus::Broken)
    {
        // TODO: log
        return;
    }

    // TODO: investigate `options` parameter
    AVFormatContext* avFormatContext = nullptr;
    if (const int ret = avformat_open_input(&avFormatContext, resource.GetURL().c_str(), nullptr, nullptr); ret == 0)
    {
        // TODO: investigate
        // avFormatContext->metadata;

        // TODO: investigate `options` parameter
        if (const int ret = avformat_find_stream_info(avFormatContext, nullptr); ret >= 0)
        {
            auto& media = resource.GetMedia();

            mmAudio* audio = new mmAudio();
            media.push_back(audio);

            // TODO: set samplerate

            // TODO: figure out whether `avformat_close_input` should be called on `avformat_...` failure
            avformat_close_input(&avFormatContext);

            resource.SetStatus(mmResourceStatus::LoadedShallow);
        }
        else
        {
            // TODO: log
            resource.SetStatus(mmResourceStatus::Broken);
        }
    }
    else
    {
        // TODO: log
        resource.SetStatus(mmResourceStatus::Broken);
    }
}

void mmResourceManager::LoadResourceDeep(mmResource& resource)
{

}

EPI_NAMESPACE_END()
