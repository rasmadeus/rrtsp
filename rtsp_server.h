#ifndef RTSP_SERVER_H
#define RTSP_SERVER_H

extern "C"
{
    #include <gst/rtsp-server/rtsp-server.h>
}

#include <QVariantHash>
#include <QString>

class RtspServer
{
public:
    RtspServer(QVariantHash const &params);
    ~RtspServer();

private:
    GstRTSPServer *_server;
    GstRTSPMediaFactory *_factory;

private:
    QString _host;
    QString _port;
    QString _mountPath;
    QString _launch;
};

#endif // RTSP_SERVER_H
