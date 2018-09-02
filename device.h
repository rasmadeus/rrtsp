#ifndef DEVICE_H
#define DEVICE_H

#include <QVariantHash>

class Device
{
public:
    virtual ~Device() = default;

public:
    virtual void start(QVariantHash const &params) = 0;
    virtual void stop() = 0;
};

#endif // DEVICE_H
