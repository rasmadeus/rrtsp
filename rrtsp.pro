QT += \
    core \
    gui \
    widgets \
    multimedia

TARGET = \
    rrtsp

TEMPLATE = \
    app

DEFINES += \
    QT_DEPRECATED_WARNINGS

CONFIG += \
    c++14

SOURCES += \
    main.cpp \
    main_view.cpp \
    gloop.cpp \
    device.cpp \
    rtsp_server.cpp \
    camera.cpp

HEADERS += \
    main_view.h \
    gloop.h \
    device.h \
    rtsp_server.h \
    camera.h

FORMS += \
    main_view.ui

unix {
    CONFIG += \
        link_pkgconfig

    PKGCONFIG += \
        glib-2.0 \
        gobject-2.0 \
        gstreamer-1.0 \
        gstreamer-rtsp-1.0 \
        gstreamer-rtsp-server-1.0
}

DISTFILES += \
    README.md
