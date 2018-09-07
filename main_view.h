#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include "camera.h"
#include "gloop.h"
#include "widget_sink.h"

#include <QMainWindow>
#include <memory>

#include "ui_main_view.h"

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView() override;

private:
    void onStart();
    void onStop();
    void onShowStream();

private:
    Ui::MainView _ui;
    std::unique_ptr<Gloop> _loop;
    std::unique_ptr<Camera> _camera;
    WidgetSink _widgetSink;
};

#endif // MAIN_VIEW_H
