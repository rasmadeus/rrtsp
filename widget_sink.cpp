#include "widget_sink.h"

WidgetSink::WidgetSink(QWidget *parent)
    : QWidget{ parent }
{
    setAttribute(Qt::WA_NativeWindow);
}
