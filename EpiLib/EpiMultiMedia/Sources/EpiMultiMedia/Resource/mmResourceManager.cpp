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

            for (epiU32 i = 0; i < avFormatContext->nb_streams; ++i)
            {
                switch (avFormatContext->streams[i]->codec->codec_type)
                {
                case AVMEDIA_TYPE_UNKNOWN: /* TODO: log */ break;
                case AVMEDIA_TYPE_AUDIO:
                {
                    mmAudio* audio = new mmAudio();
                    media.push_back(audio);
                } break;
                }
            }

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
    if (auto status = resource.GetStatus();
        status != mmResourceStatus::Empty &&
        status != mmResourceStatus::LoadedShallow &&
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

            for (epiU32 streamIdx = 0; streamIdx < avFormatContext->nb_streams; ++streamIdx)
            {
                switch (avFormatContext->streams[streamIdx]->codec->codec_type)
                {
                case AVMEDIA_TYPE_UNKNOWN: /* TODO: log */ break;
                case AVMEDIA_TYPE_AUDIO:
                {
                    mmAudio* audio = nullptr;
                    if (resource.GetStatus() == mmResourceStatus::LoadedShallow)
                    {
                        mmMediaBase* mediaBase = media[streamIdx];
                        if (audio = epiAs<mmAudio>(mediaBase); audio == nullptr)
                        {
                            // TODO: log
                        }
                    }
                    else
                    {
                        audio = new mmAudio();
                        media.push_back(audio);
                    }

                    if (audio != nullptr)
                    {
                        AVCodecContext* avCodecContextOrig = avFormatContext->streams[streamIdx]->codec;
                        if (AVCodec* avCodec = avcodec_find_decoder(avCodecContextOrig->codec_id); avCodec != nullptr)
                        {
                            if (AVCodecContext* avCodecContext = avcodec_alloc_context3(avCodec))
                            {
                                if (avcodec_copy_context(avCodecContext, avCodecContextOrig) == 0)
                                {
                                    // TODO: investigate `options` parameter
                                    if (avcodec_open2(avCodecContext, avCodec, nullptr) == 0)
                                    {
                                        audio->SetSampleRate(avCodecContext->sample_rate);
                                        audio->SetBitRate(avCodecContext->bit_rate);

                                        // TODO: set CodecName: avCodecContext->codec->long_name
                                        // TODO: set TicksPerFrame: avCodecContext->ticks_per_frame

                                        epiArray<dSeries1Df>& channels = audio->GetChannels();
                                        epiFor(avCodecContext->channels)
                                        {
                                            dSeries1Df& series = channels.PushBack();

                                            // TODO: calculate the total number of samples
                                            series.Reserve(10000);
                                        }

                                        AVPacket packet;
                                        AVFrame* frame = av_frame_alloc();

                                        epiS32 ret;
                                        while ((ret = av_read_frame(avFormatContext, &packet)) == 0)
                                        {
                                            if (packet.stream_index == streamIdx)
                                            {
                                                avcodec_send_packet(avCodecContext, &packet);
                                                while ((ret = avcodec_receive_frame(avCodecContext, frame)) == 0)
                                                {
                                                    const epiS32 sampleSize = av_get_bytes_per_sample(avCodecContext->sample_fmt);
                                                    if (sampleSize < 0)
                                                    {
                                                        // TODO: log
                                                        break;
                                                    }

                                                    epiAssert(audio->GetSampleRate() == frame->sample_rate);
                                                    epiAssert(audio->GetChannels().Size() == frame->channels);

                                                    for (epiS32 frameIdx = 0; frameIdx < frame->nb_samples; ++frameIdx)
                                                    {
                                                        for (epiS32 channelIdx = 0; channelIdx < frame->channels; ++channelIdx)
                                                        {
                                                            epiAssert(avCodecContext->sample_fmt == AV_SAMPLE_FMT_FLTP, "use sws converter");
                                                            const epiFloat* sample = reinterpret_cast<const epiFloat*>(frame->data[channelIdx] + frameIdx * sampleSize);

                                                            epiFloat& dstSample = channels[channelIdx].PushBack();
                                                            dstSample = *sample;
                                                        }
                                                    }
                                                }

                                                switch (ret)
                                                {
                                                case AVERROR_EOF: break;
                                                case AVERROR(EAGAIN): /* TODO: log: output is not available in this state - user must try to send new input */ break;
                                                case AVERROR(EINVAL): /* TODO: log: codec not opened, or it is an encoder */ break;
                                                case AVERROR_INPUT_CHANGED: /* TODO: log: current decoded frame has changed parameters */ break;
                                                default: /* TODO: log */ break;
                                                }

                                                if (ret != AVERROR_EOF && ret != AVERROR(EAGAIN))
                                                {
                                                    break;
                                                }
                                            }
                                        }

                                        av_frame_free(&frame);
                                        av_packet_unref(&packet);

                                        if (ret != 0)
                                        {
                                            // TODO: log
                                        }
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

                                avcodec_free_context(&avCodecContext);
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
                    }
                } break;
                }
            }

            // TODO: figure out whether `avformat_close_input` should be called on `avformat_...` failure
            avformat_close_input(&avFormatContext);

            resource.SetStatus(mmResourceStatus::LoadedDeep);
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

EPI_NAMESPACE_END()
