#include <QtGlobal>
#include "gloop.h"

Gloop::Gloop()
    : _loop{ g_main_loop_new(nullptr, FALSE) }
    , _thread{ g_main_loop_run, _loop }
{
}

Gloop::~Gloop()
{
    g_main_loop_quit(_loop);
    _thread.join();
    g_main_loop_unref(_loop);
}
