#include "main_view.h"

MainView::MainView(QWidget *parent)
    : QMainWindow{ parent }
{
    _ui.setupUi(this);
    gst_init(nullptr, nullptr);
    _loop = std::make_unique<Gloop>();
    _camera = std::make_unique<Camera>();

    connect(_ui.start, &QPushButton::clicked, this, &MainView::onStart);
    connect(_ui.stop, &QPushButton::clicked, this, &MainView::onStop);
}

void MainView::onStart()
{
    _ui.stop->setEnabled(true);
    _ui.start->setEnabled(false);
    _camera->start({
        { QStringLiteral("host"), _ui.host->text() },
        { QStringLiteral("port"), _ui.port->text() },
        { QStringLiteral("mount_path"), _ui.mountPath->text() },
        { QStringLiteral("launch"), _ui.launch->text() },
    });
}

void MainView::onStop()
{
    _ui.stop->setEnabled(false);
    _ui.start->setEnabled(true);
    _camera->stop();
}
