extern "C"
{
    #include <gst/gst.h>
    #include <gst/video/video-overlay-composition.h>
}

#include <QDebug>
#include "rtsp_client.h"

namespace
{
    void on_pad_added(GstElement *element, GstPad *pad, gpointer data)
    {
        qDebug() << "Pad added";
        GstElement *decodebin = static_cast<GstElement*>(data);
        GstPad *sink_pad = gst_element_get_static_pad (decodebin, "sink");
        if (gst_pad_is_linked (sink_pad)) {
            qDebug() << "Already linked ignore1";
            return;
        }

         auto ret = gst_pad_link (pad, sink_pad);
         qDebug() << "Link pad" << GST_PAD_LINK_FAILED(ret);
    }

    void on_decoded_pad_added(GstElement *element, GstPad *pad, gpointer data)
    {
        qDebug() << "Decoded Pad added";

        GstElement *decodebin = static_cast<GstElement*>(data);
        GstPad *sink_pad = gst_element_get_static_pad (decodebin, "sink");
        if (gst_pad_is_linked (sink_pad)) {
            qDebug() << "Already linked ignore2";
            return;
        }

         auto ret = gst_pad_link (pad, sink_pad);
         qDebug() << "Link pad 2" << GST_PAD_LINK_FAILED(ret);
    }
}

class GstElementGuard
{
public:
     GstElementGuard(GstElement *element)
         : _element{ element }
     {
     }

     ~GstElementGuard()
     {
         if (_element)
             gst_object_unref(_element);
     }

private:
     GstElement *_element;
};

struct Data
{

};

RtspClient::RtspClient(WId id)
{
    auto pipeline = gst_pipeline_new ("RtspClient");
    GstElementGuard pipelineGuard{ pipeline };

    auto rtspsrc = gst_element_factory_make ("rtspsrc", "rtspsrc");
    if (!rtspsrc)
    {
        qDebug() << "Failed to creare rtspsrc";
        return;
    }

    auto decodebin = gst_element_factory_make ("decodebin", "decodebin");
    if (!decodebin)
    {
        qDebug() << "Failed to create dcodebin";
        return;
    }

    auto autovideosink = gst_element_factory_make ("appsink", "autovideosink");
    if (!autovideosink)
    {
        qDebug() << "Failed to create autovideosink";
        return;
    }

    gst_bin_add_many(GST_BIN(pipeline), rtspsrc, decodebin, autovideosink, nullptr);

    g_signal_connect (rtspsrc, "pad-added", G_CALLBACK (on_pad_added), decodebin);
    g_signal_connect (decodebin, "pad-added", G_CALLBACK (on_decoded_pad_added), autovideosink);

    g_object_set(rtspsrc, "location", "rtsp://127.0.0.1:5000/test", nullptr);
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(autovideosink) , id);

    auto playState = gst_element_set_state (pipeline, GST_STATE_PLAYING);
    qDebug() << "Play state:" << playState;
}

RtspClient::~RtspClient()
{
}
