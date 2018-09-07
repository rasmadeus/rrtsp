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
    camera.cpp \
    widget_sink.cpp \
    rtsp_client.cpp

HEADERS += \
    main_view.h \
    gloop.h \
    device.h \
    rtsp_server.h \
    camera.h \
    widget_sink.h \
    rtsp_client.h

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


win32 {
    GSTREAMER_HOME = C:/gstreamer/1.0/x86

    INCLUDEPATH += \
        $$GSTREAMER_HOME/include/gstreamer-1.0 \
        $$GSTREAMER_HOME/include/glib-2.0 \
        $$GSTREAMER_HOME/lib/glib-2.0/include

    LIBS += \
        -L$$GSTREAMER_HOME/lib \
        -lgstreamer-1.0 \
        -lglib-2.0 \
        -lintl \
        -lgobject-2.0 \
        -lgstvideo-1.0 \
        -lgstbase-1.0 \
        -lgstrtsp-1.0 \
        -lgstrtspserver-1.0 \
        -lsupc++
}

DISTFILES += \
    README.md
