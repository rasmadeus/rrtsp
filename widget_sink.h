#ifndef WIDGETSINK_H
#define WIDGETSINK_H

#include <QWidget>

class WidgetSink : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetSink(QWidget *parent = nullptr);
};

#endif // WIDGETSINK_H
