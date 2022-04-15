#pragma once

#include <map>
#include <list>
#include <queue>
#include<list>
#include <vector>
#include <string>
#include <functional>
#include <ucontext.h>

#include "log.h"

typedef enum {
    INIT = 0,
    READYING = 1,
    WAITING = 2,
    FINISHED = 3
}FiberStatus;

class Fiber;
class XFiber {
public:
    XFiber();

    ~XFiber();

    void WakeupFiber(Fiber *fiber);

    Fiber* CreateFiber(std::function<void()> run, size_t stack_size = 0, std::string fiber_name="");

    void Dispatch();

    void Yield();

    void SwitchToSchedFiber();

    bool RegisterFdToSchedWithFiber(int fd, Fiber *fiber);

    bool UnregisterFdFromSched(int fd);

    bool RegisterFdToEpoll(int fd);

    bool UnregisterFdFromEpoll(int fd);

    bool AddReadyFibers(Fiber* fiber);

    void EventLoop();
        ucontext_t *
        SchedCtx();

    static XFiber *xfiber() {
        static thread_local XFiber xf;
        return &xf;
    }

    inline Fiber *CurrFiber() {
        return curr_fiber_;
    }

//private:
    int efd_;
    
    
    std::list<Fiber*> ready_fibers_,work_fibers_;
    ucontext_t sched_ctx_;

    Fiber *curr_fiber_;

    /*struct WaitingFibers {
        Fiber *r_, *w_;
        WaitingFibers() {
            r_ = nullptr;
            w_ = nullptr;
        }
    };*/

    std::map<int, Fiber*> io_waiting_fibers_;
    
};


class Fiber
{
public:
    Fiber(std::function<void ()> run, size_t stack_size, std::string fiber_name);

    ~Fiber();

    ucontext_t* Ctx();

    std::string Name();

    bool IsFinished();

    void SetXFiber(XFiber *xfiber);
    
    void Run();

    void Yield();

    uint64_t Seq();

    static void Start(Fiber *fiber);

private:
    uint64_t seq_;
    XFiber *xfiber_;
    std::string fiber_name_;
    FiberStatus status_;
    ucontext_t ctx_;
    uint8_t *stack_ptr_;
    size_t stack_size_;
    std::function<void ()> run_;
};

