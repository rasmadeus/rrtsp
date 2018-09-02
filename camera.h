#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include "rtsp_server.h"
#include "device.h"

class Camera : public Device
{
public:
    void start(QVariantHash const &params) override;
    void stop() override;

private:
    std::unique_ptr<RtspServer> _server;
};

#endif // CAMERA_H
