extern "C"
{
    #include <gst/gst.h>
}

#include "rtsp_server.h"
#include <QDebug>

namespace
{
    GstRTSPFilterResult allClientFilter (GstRTSPServer*, GstRTSPClient*, gpointer)
    {
        return GST_RTSP_FILTER_REMOVE;
    }

    gboolean cleanupSessions(gpointer userData)
    {
        auto server = static_cast<GstRTSPServer*>(userData);
        auto pool = gst_rtsp_server_get_session_pool(server);
        gst_rtsp_session_pool_cleanup(pool);
        g_object_unref(pool);
        return TRUE;
    }
}

RtspServer::RtspServer(QVariantHash const &params)
    : _server{ gst_rtsp_server_new() }
    , _factory{ gst_rtsp_media_factory_new() }
    , _host{ params.value(QStringLiteral("host")).toString() }
    , _port{ params.value(QStringLiteral("port")).toString() }
    , _mountPath{ params.value(QStringLiteral("mount_path")).toString() }
    , _launch{ params.value(QStringLiteral("launch")).toString() }
{
    gst_rtsp_server_set_address(_server, _host.toUtf8().constData());
    gst_rtsp_server_set_service(_server, _port.toUtf8().constData());
    auto mounts = gst_rtsp_server_get_mount_points(_server);
    gst_rtsp_media_factory_set_launch(_factory, _launch.toUtf8().constData());
    gst_rtsp_media_factory_set_shared(_factory, TRUE);
    gst_rtsp_mount_points_add_factory (mounts, _mountPath.toUtf8().constData(), _factory);
    g_object_unref (mounts);
    gst_rtsp_server_attach(_server, nullptr);
    g_timeout_add_seconds(10, ::cleanupSessions, _server);
    qDebug() << "Rtsp server started as" << _launch.toUtf8().constData();
}

RtspServer::~RtspServer()
{
    auto mounts = gst_rtsp_server_get_mount_points(_server);
    gst_rtsp_mount_points_remove_factory(mounts, _mountPath.toUtf8().constData());
    g_object_unref (mounts);
    gst_rtsp_server_client_filter(_server, ::allClientFilter, nullptr);
    qDebug() << "Rtsp server stopped";
}
