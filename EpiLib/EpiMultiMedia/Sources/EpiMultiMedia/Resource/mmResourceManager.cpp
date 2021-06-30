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
#include "EpiMultimedia/mmVideo.h"

extern "C"
{

#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"

}

namespace
{

EPI_NAMESPACE_USING()

epiBool ParseMedia(mmResource& resource, AVFormatContext& avFormatContext, const std::map<epiS32, mmMediaBase*>& streams)
{
    struct ParsingContext
    {
        AVCodecContext* CodecContext{nullptr};
        SwsContext* SWSContext{nullptr};
        AVFrame* FrameDecoded{nullptr};
        epiS32 BytesPerSample{-1};

        ~ParsingContext()
        {
            if (CodecContext != nullptr)
            {
                avcodec_free_context(&CodecContext);
            }

            if (SWSContext != nullptr)
            {
                sws_freeContext(SWSContext);
            }

            if (FrameDecoded != nullptr)
            {
                av_frame_free(&FrameDecoded);
            }
        }
    };

    std::map<epiS32, ParsingContext> parsingContextMap;
    for (const auto& [streamIdx, media] : streams)
    {
        ParsingContext& parsingContext = parsingContextMap[streamIdx];

        AVCodecContext* avCodecContextOrig = avFormatContext.streams[streamIdx]->codec;
        AVCodec* avCodec = avcodec_find_decoder(avCodecContextOrig->codec_id);
        if (avCodec == nullptr)
        {
            epiLogError("`avcodec_find_decoder` has failed: codec_id=`{}`, url=`{}`!", avCodecContextOrig->codec_id, resource.GetURL());
            return false;
        }

        AVCodecContext* avCodecContext = avcodec_alloc_context3(avCodec);
        if (avCodecContext == nullptr)
        {
            epiLogError("`avcodec_alloc_context3` has failed: url=`{}`!", resource.GetURL());
            return false;
        }

        parsingContext.CodecContext = avCodecContext;

        if (avcodec_copy_context(avCodecContext, avCodecContextOrig) != 0)
        {
            epiLogError("`avcodec_copy_context` has failed: url=`{}`!", resource.GetURL());
            return false;
        }

        // TODO: investigate `options` parameter
        if (avcodec_open2(avCodecContext, avCodec, nullptr) != 0)
        {
            epiLogError("`avcodec_open2` has failed: url=`{}`!", resource.GetURL());
            return false;
        }
    }

    for (const auto& [streamIdx, media] : streams)
    {
        epiAssert(parsingContextMap.find(streamIdx) != parsingContextMap.end());
        ParsingContext& parsingContext = parsingContextMap[streamIdx];
        epiAssert(parsingContext.CodecContext != nullptr);

        if (mmAudio* audio = epiAs<mmAudio>(media))
        {
            if (parsingContext.BytesPerSample = av_get_bytes_per_sample(parsingContext.CodecContext->sample_fmt);
                parsingContext.BytesPerSample < 0)
            {
                epiLogError("Can't calculate sample size from sample format: sample_fmt=`{}`, url=`{}`!",
                            parsingContext.CodecContext->sample_fmt,
                            resource.GetURL());
                return false;
            }

            audio->SetSampleRate(parsingContext.CodecContext->sample_rate);
            audio->SetBitRate(parsingContext.CodecContext->bit_rate);

            // TODO: set CodecName: parsingContext.CodecContext->codec->long_name
            // TODO: set TicksPerFrame: parsingContext.CodecContext->ticks_per_frame

            epiArray<dSeries1Df>& channels = audio->GetChannels();
            epiFor(parsingContext.CodecContext->channels)
            {
                dSeries1Df& series = channels.PushBack();

                // TODO: calculate the total number of samples
                series.Reserve(10000);
            }
        }
        else if (mmVideo* video = epiAs<mmVideo>(media))
        {
            const epiFloat frameRate = parsingContext.CodecContext->framerate.num / static_cast<epiFloat>(parsingContext.CodecContext->framerate.den);
            video->SetFrameRate(static_cast<epiU32>(std::ceil(frameRate)));
            video->SetBitRate(parsingContext.CodecContext->bit_rate);

            // TODO: set CodecName: parsingContext.CodecContext->codec->long_name
            // TODO: set TicksPerFrame: parsingContext.CodecContext->ticks_per_frame

            epiArray<mmFrame>& frames = video->GetFrames();
            // TODO: reserve

            parsingContext.SWSContext = sws_getContext(parsingContext.CodecContext->coded_width,
                                                       parsingContext.CodecContext->coded_height,
                                                       parsingContext.CodecContext->pix_fmt,
                                                       parsingContext.CodecContext->width,
                                                       parsingContext.CodecContext->height,
                                                       AV_PIX_FMT_RGB24,
                                                       SWS_BILINEAR,
                                                       nullptr,
                                                       nullptr,
                                                       nullptr);
            epiAssert(parsingContext.SWSContext != nullptr);

            parsingContext.FrameDecoded = av_frame_alloc();
            epiAssert(parsingContext.FrameDecoded != nullptr);

            const epiS32 imageBytes = av_image_alloc(parsingContext.FrameDecoded->data,
                                                     parsingContext.FrameDecoded->linesize,
                                                     parsingContext.CodecContext->width,
                                                     parsingContext.CodecContext->height,
                                                     AV_PIX_FMT_RGB24,
                                                     1);
            epiAssert(imageBytes > 0);
        }
        else if (mmImage* image = epiAs<mmImage>(media))
        {
            parsingContext.SWSContext = sws_getContext(parsingContext.CodecContext->coded_width,
                                                       parsingContext.CodecContext->coded_height,
                                                       parsingContext.CodecContext->pix_fmt,
                                                       parsingContext.CodecContext->width,
                                                       parsingContext.CodecContext->height,
                                                       AV_PIX_FMT_RGB24,
                                                       SWS_BILINEAR,
                                                       nullptr,
                                                       nullptr,
                                                       nullptr);
            epiAssert(parsingContext.SWSContext != nullptr);

            parsingContext.FrameDecoded = av_frame_alloc();
            epiAssert(parsingContext.FrameDecoded != nullptr);

            const epiS32 imageBytes = av_image_alloc(parsingContext.FrameDecoded->data,
                                                     parsingContext.FrameDecoded->linesize,
                                                     parsingContext.CodecContext->width,
                                                     parsingContext.CodecContext->height,
                                                     AV_PIX_FMT_RGB24,
                                                     1);
            epiAssert(imageBytes > 0);
        }
        else
        {
            epiLogError("Unhandled media type: `{}`!", media->ToString());
        }
    }

    AVPacket packet;
    AVFrame* frameRaw = av_frame_alloc();
    if (frameRaw == nullptr)
    {
        epiLogError("Failed to allocate frame with `av_frame_alloc`: url=`{}`!", resource.GetURL());
    }

    epiS32 ret;
    while ((ret = av_read_frame(&avFormatContext, &packet)) == 0)
    {
        ParsingContext& parsingContext = parsingContextMap[packet.stream_index];
        epiAssert(parsingContext.CodecContext != nullptr);

        switch (avcodec_send_packet(parsingContext.CodecContext, &packet))
        {
        case 0: break;
        case AVERROR(EAGAIN):
        {
            epiLogError("`avcodec_send_packet` has returned `AVERROR(EAGAIN)` (input is not accepted in the current "
                        "state - user must read output with avcodec_receive_frame() (once all output is read, the "
                        "packet should be resent, and the call will not fail with EAGAIN)): url=`{}`!",
                        resource.GetURL());
        } break;
        case AVERROR_EOF:
        {
            epiLogError("`avcodec_send_packet` has returned `AVERROR_EOF` (the decoder has been flushed, and "
                        "no new packets can be sent to it(also returned if more than 1 flush packet is sent)): url=`{}`!",
                        resource.GetURL());
        } break;
        case AVERROR(EINVAL):
        {
            epiLogError("`avcodec_send_packet` has returned `AVERROR(EINVAL)` (codec not opened, it is an "
                        "encoder, or requires flush): url=`{}`!",
                        resource.GetURL());
        } break;
        case AVERROR(ENOMEM):
        {
            epiLogError("`avcodec_send_packet` has returned `AVERROR(ENOMEM)` (failed to add packet to internal "
                        "queue, or similar other errors : legitimate decoding errors): url=`{}`!",
                        resource.GetURL());
        } break;
        }

        while ((ret = avcodec_receive_frame(parsingContext.CodecContext, frameRaw)) == 0)
        {
            epiAssert(streams.find(packet.stream_index) != streams.end());
            mmMediaBase* media = streams.at(packet.stream_index);

            if (mmAudio* audio = epiAs<mmAudio>(media))
            {
                epiArray<dSeries1Df>& channels = audio->GetChannels();

                epiAssert(audio->GetSampleRate() == frameRaw->sample_rate);
                epiAssert(audio->GetChannels().Size() == frameRaw->channels);

                for (epiS32 frameIdx = 0; frameIdx < frameRaw->nb_samples; ++frameIdx)
                {
                    for (epiS32 channelIdx = 0; channelIdx < frameRaw->channels; ++channelIdx)
                    {
                        epiAssert(parsingContext.CodecContext->sample_fmt == AV_SAMPLE_FMT_FLTP, "use sws converter");
                        const epiFloat* sample = reinterpret_cast<const epiFloat*>(frameRaw->data[channelIdx] + frameIdx * parsingContext.BytesPerSample);

                        epiFloat& dstSample = channels[channelIdx].PushBack();
                        dstSample = *sample;
                    }
                }
            }
            else if (mmVideo* video = epiAs<mmVideo>(media))
            {
                sws_scale(parsingContext.SWSContext,
                          frameRaw->data,
                          frameRaw->linesize,
                          0,
                          parsingContext.CodecContext->height,
                          parsingContext.FrameDecoded->data,
                          parsingContext.FrameDecoded->linesize);

                mmImage& imageDst = video->GetFrames().PushBack().GetImage();
                imageDst.SetWidth(parsingContext.CodecContext->width);
                imageDst.SetHeight(parsingContext.CodecContext->height);

                // TODO: set bit depth
                // imageDst.SetBitDepth(parsingContext.FrameDecoded->bit)

#ifdef EPI_BUILD_DEBUG
                for (epiS32 i = 1; i < AV_NUM_DATA_POINTERS; ++i)
                {
                    epiAssert(parsingContext.FrameDecoded->data[i] == nullptr);
                    epiAssert(parsingContext.FrameDecoded->linesize[i] == 0);
                }
#endif // EPI_BUILD_DEBUG

                epiArray<epiByte>& dataDst = imageDst.GetData();
                const epiS32 bufferSize = av_image_get_buffer_size(AV_PIX_FMT_RGB24,
                                                                   parsingContext.CodecContext->width,
                                                                   parsingContext.CodecContext->height,
                                                                   1);
                epiAssert(bufferSize > 0);

                dataDst.Resize(bufferSize);

                const epiS32 bytesCopied = av_image_copy_to_buffer(dataDst.GetData(),
                                                                   dataDst.GetSize(),
                                                                   parsingContext.FrameDecoded->data,
                                                                   parsingContext.FrameDecoded->linesize,
                                                                   AV_PIX_FMT_RGB24,
                                                                   parsingContext.CodecContext->width,
                                                                   parsingContext.CodecContext->height,
                                                                   1);
                epiAssert(bytesCopied == bufferSize);
            }
            else if (mmImage* image = epiAs<mmImage>(media))
            {
                sws_scale(parsingContext.SWSContext,
                          frameRaw->data,
                          frameRaw->linesize,
                          0,
                          parsingContext.CodecContext->height,
                          parsingContext.FrameDecoded->data,
                          parsingContext.FrameDecoded->linesize);

                image->SetWidth(parsingContext.CodecContext->width);
                image->SetHeight(parsingContext.CodecContext->height);

                // TODO: set bit depth
                // imageDst.SetBitDepth(parsingContext.FrameDecoded->bit)

#ifdef EPI_BUILD_DEBUG
                for (epiS32 i = 1; i < AV_NUM_DATA_POINTERS; ++i)
                {
                    epiAssert(parsingContext.FrameDecoded->data[i] == nullptr);
                    epiAssert(parsingContext.FrameDecoded->linesize[i] == 0);
                }
#endif // EPI_BUILD_DEBUG

                epiArray<epiByte>& dataDst = image->GetData();
                const epiS32 bufferSize = av_image_get_buffer_size(AV_PIX_FMT_RGB24,
                                                                   parsingContext.CodecContext->width,
                                                                   parsingContext.CodecContext->height,
                                                                   1);
                epiAssert(bufferSize > 0);

                dataDst.Resize(bufferSize);

                const epiS32 bytesCopied = av_image_copy_to_buffer(dataDst.GetData(),
                                                                   dataDst.GetSize(),
                                                                   parsingContext.FrameDecoded->data,
                                                                   parsingContext.FrameDecoded->linesize,
                                                                   AV_PIX_FMT_RGB24,
                                                                   parsingContext.CodecContext->width,
                                                                   parsingContext.CodecContext->height,
                                                                   1);
                epiAssert(bytesCopied == bufferSize);
            }
        }

        switch (ret)
        {
        case AVERROR_EOF: break;
        case AVERROR(EAGAIN): break;
        case AVERROR(EINVAL):
        {
            epiLogError("`avcodec_receive_frame` has returned `AVERROR(EINVAL)` (codec not opened, or it is an encoder): url=`{}`!", resource.GetURL());
        } break;
        case AVERROR_INPUT_CHANGED:
        {
            epiLogError("`avcodec_receive_frame` has returned `AVERROR_INPUT_CHANGED` (current decoded frame has changed parameters): url=`{}`!", resource.GetURL());
        } break;
        default:
        {
            epiLogError("`avcodec_receive_frame` has returned an error code: code=`{}`, url=`{}`!", ret, resource.GetURL());
        } break;
        }

        if (ret != AVERROR_EOF && ret != AVERROR(EAGAIN))
        {
            break;
        }
    }

    av_frame_free(&frameRaw);
    av_packet_unref(&packet);

    if (ret != AVERROR_EOF)
    {
        epiLogError("`av_read_frame` has returned an error code: code=`{}`, url=`{}`!", ret, resource.GetURL());
    }

    return true;
}

}

EPI_NAMESPACE_BEGIN()

mmResource* mmResourceManager::LoadResource(const epiChar* url, epiBool deepLoad)
{
    std::unique_ptr<mmResource>& resource = m_Resources[url];
    if (!resource)
    {
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
    }

    return resource.get();
}

void mmResourceManager::LoadResourceShallow(mmResource& resource)
{
    if (auto status = resource.GetStatus();
        status != mmResourceStatus::Empty &&
        status != mmResourceStatus::Broken)
    {
        // TODO: log string representation of `status`
        epiLogWarn("`LoadResourceShallow` has early returned: status=`{}`, url=`{}`!", status, resource.GetURL());
        return;
    }

    resource.SetStatus(mmResourceStatus::LoadingShallow);

    do
    {
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

                const epiBool isImage = avFormatContext->nb_streams == 1 &&
                                        avFormatContext->streams[0]->codec->codec_type == AVMEDIA_TYPE_VIDEO &&
                                        (
                                            strncmp(avFormatContext->iformat->name, "image2", strlen("image2")) == 0 ||
                                            strncmp(avFormatContext->iformat->name, "png_pipe", strlen("png_pipe")) == 0
                                        );


                if (isImage)
                {
                    media.push_back(new mmImage());
                }
                else
                {
                    for (epiU32 i = 0; i < avFormatContext->nb_streams; ++i)
                    {
                        switch (avFormatContext->streams[i]->codec->codec_type)
                        {
                        case AVMEDIA_TYPE_UNKNOWN: epiLogWarn("Unknown media type has occurred: url=`{}`!", resource.GetURL()); break;
                        case AVMEDIA_TYPE_AUDIO:
                        {
                            media.push_back(new mmAudio());
                        } break;
                        case AVMEDIA_TYPE_VIDEO:
                        {
                            media.push_back(new mmVideo());
                        } break;
                        }
                    }
                }

                // TODO: set samplerate

                // TODO: figure out whether `avformat_close_input` should be called on `avformat_...` failure
                avformat_close_input(&avFormatContext);
            }
            else
            {
                epiLogWarn("Failed to retrieve stream info with `avformat_find_stream_info`! The resource is broken: url=`{}`!", resource.GetURL());
                break;
            }
        }
        else
        {
            epiLogWarn("Failed to open with `avformat_open_input`! The resource is broken: url=`{}`!", resource.GetURL());
            break;
        }

        resource.SetStatus(mmResourceStatus::LoadedShallow);
        return;
    } while (0);

    resource.SetStatus(mmResourceStatus::Broken);
}

void mmResourceManager::LoadResourceDeep(mmResource& resource)
{
    if (auto status = resource.GetStatus();
        status != mmResourceStatus::Empty &&
        status != mmResourceStatus::LoadedShallow &&
        status != mmResourceStatus::Broken)
    {
        // TODO: log string representation of `status`
        epiLogWarn("`LoadResourceDeep` has early returned: status=`{}`, url=`{}`!", status, resource.GetURL());
        return;
    }

    const mmResourceStatus previuosStatus = resource.GetStatus();
    resource.SetStatus(mmResourceStatus::LoadingDeep);

    do
    {
        // TODO: investigate `options` parameter
        AVFormatContext* avFormatContext = nullptr;
        if (const int ret = avformat_open_input(&avFormatContext, resource.GetURL().c_str(), nullptr, nullptr); ret == 0)
        {
            // TODO: investigate
            // avFormatContext->metadata;

            // TODO: investigate `options` parameter
            if (const int ret = avformat_find_stream_info(avFormatContext, nullptr); ret >= 0)
            {
                std::map<epiS32, mmMediaBase*> streams;

                auto& media = resource.GetMedia();
                const epiBool isImage = avFormatContext->nb_streams == 1 &&
                                        avFormatContext->streams[0]->codec->codec_type == AVMEDIA_TYPE_VIDEO &&
                                        (
                                            strncmp(avFormatContext->iformat->name, "image2", strlen("image2")) == 0 ||
                                            strncmp(avFormatContext->iformat->name, "png_pipe", strlen("png_pipe")) == 0
                                        );

                if (isImage)
                {
                    mmImage* image = nullptr;
                    if (previuosStatus == mmResourceStatus::LoadedShallow)
                    {
                        mmMediaBase* mediaBase = media[0];
                        if (image = epiAs<mmImage>(mediaBase); image == nullptr)
                        {
                            epiLogError("Media stream matching has failed (`mmImage` was expected, but `{}` occurred): url=`{}`!", mediaBase->GetMetaClass().GetName(), resource.GetURL());
                        }
                    }
                    else if (previuosStatus == mmResourceStatus::Empty)
                    {
                        image = new mmImage();
                        media.push_back(image);
                    }

                    epiAssert(image != nullptr);
                    streams[0] = image;
                }
                else
                {
                    for (epiU32 streamIdx = 0; streamIdx < avFormatContext->nb_streams; ++streamIdx)
                    {
                        switch (avFormatContext->streams[streamIdx]->codec->codec_type)
                        {
                        case AVMEDIA_TYPE_UNKNOWN: epiLogWarn("Unknown media type has occurred: url=`{}`!", resource.GetURL()); break;
                        case AVMEDIA_TYPE_AUDIO:
                        {
                            mmAudio* audio = nullptr;
                            if (previuosStatus == mmResourceStatus::LoadedShallow)
                            {
                                mmMediaBase* mediaBase = media[streamIdx];
                                if (audio = epiAs<mmAudio>(mediaBase); audio == nullptr)
                                {
                                    epiLogError("Media stream matching has failed (`mmAudio` was expected, but `{}` occurred): url=`{}`!", mediaBase->GetMetaClass().GetName(), resource.GetURL());
                                }
                            }
                            else if (previuosStatus == mmResourceStatus::Empty)
                            {
                                audio = new mmAudio();
                                media.push_back(audio);
                            }

                            epiAssert(audio != nullptr);
                            streams[streamIdx] = audio;
                        } break;
                        case AVMEDIA_TYPE_VIDEO:
                        {
                            mmVideo* video = nullptr;
                            if (previuosStatus == mmResourceStatus::LoadedShallow)
                            {
                                mmMediaBase* mediaBase = media[streamIdx];
                                if (video = epiAs<mmVideo>(mediaBase); video == nullptr)
                                {
                                    epiLogError("Media stream matching has failed (`mmVideo` was expected, but `{}` occurred): url=`{}`!", mediaBase->GetMetaClass().GetName(), resource.GetURL());
                                }
                            }
                            else if (previuosStatus == mmResourceStatus::Empty)
                            {
                                video = new mmVideo();
                                media.push_back(video);
                            }

                            epiAssert(video != nullptr);
                            streams[streamIdx] = video;
                        } break;
                        }
                    }
                }

                const epiBool parseMediaSucceed = ParseMedia(resource, *avFormatContext, streams);

                // TODO: figure out whether `avformat_close_input` should be called on `avformat_...` failure
                avformat_close_input(&avFormatContext);

                if (!parseMediaSucceed)
                {
                    break;
                }
            }
            else
            {
                epiLogWarn("Failed to retrieve stream info with `avformat_find_stream_info`! The resource is broken: url=`{}`!", resource.GetURL());
                break;
            }
        }
        else
        {
            epiLogWarn("Failed to open with `avformat_open_input`! The resource is broken: url=`{}`!", resource.GetURL());
            break;
        }

        resource.SetStatus(mmResourceStatus::LoadedDeep);
        return;
    } while (0);

    resource.SetStatus(mmResourceStatus::Broken);
}

EPI_NAMESPACE_END()
