#include "cr-sync-work-waiter.hpp"
#include "../../system/sys-log.hpp"
#include "../cr-function-loader.hpp"
#include "cr-sync-queued-semaphore.hpp"

#include <iostream>

void gearoenix::core::sync::WorkWaiter::wait_loop()
{
    while (running) {
        GXLOGD("Going to wait.");
        semaphore->lock();
        GXLOGD("Going to unload.");
        function_loader->unload();
    }
    running = true;
}

gearoenix::core::sync::WorkWaiter::WorkWaiter()
    : semaphore(new QueuedSemaphore())
    , function_loader(new FunctionLoader())
    , thread(std::bind(&WorkWaiter::wait_loop, this))
{
}

gearoenix::core::sync::WorkWaiter::~WorkWaiter()
{
    running = false;
    while (!running) {
        semaphore->release();
    }
    thread.join();
}

void gearoenix::core::sync::WorkWaiter::push(std::function<void()> f)
{
    function_loader->load(f);
    semaphore->release();
}
