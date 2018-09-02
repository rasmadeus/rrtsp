#include "camera.h"

void Camera::start(QVariantHash const &params)
{
    _server = std::make_unique<RtspServer>(params);
}

void Camera::stop()
{
    _server.reset();
}
