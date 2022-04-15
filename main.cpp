#include <stdio.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <cstring>
#include <memory>

#include "xfiber.h"
#include "listener.h"
#include "conn.h"

using namespace std;


void sigint_action(int sig) {
    std::cout << "exit..." << std::endl;
    exit(0);    
}
void func1(){

}
int main() {
    signal(SIGINT, sigint_action);

    XFiber *xfiber = XFiber::xfiber();
    /*xfiber->CreateFiber([&]() {
        cout << "hello world 11" << endl;
        xfiber->Yield();
        cout << "hello world 12" << endl;
         xfiber->Yield();
        cout << "hello world 13" << endl;
        xfiber->Yield();
        cout << "hello world 14" << endl;
        cout << "hello world 15" << endl;

    }, 0, "f1");

    xfiber->CreateFiber([]() {
        cout << "hello world 2" << endl;
    }, 0, "f2");*/
    

    Fiber* accepter=xfiber->CreateFiber([&]{
        Listener listener = Listener::ListenTCP(6379);
        int i=0;
        while (true) {
            shared_ptr<Connection> conn = listener.Accept();//已经注册到epoll上，接下来注册对应协程
            Fiber* workFiber=xfiber->CreateFiber([conn] {
                while (true) {
                    char recv_buf[512];
                    int n = conn->Read(recv_buf, 512);
                    if (n <= 0) {
                        break;
                    }
                    recv_buf[n] = '\0';
                    cout << "recv: " << recv_buf << endl;
                    const char *rsp = "+OK\r\n";
                    conn->Write(rsp, strlen(rsp));
                }
            }, 0, "server"+to_string(i++));
            xfiber->RegisterFdToSchedWithFiber(conn->RawFd(),workFiber);
        }
        
    },0,"accepter");
    xfiber->WakeupFiber(accepter);
    Fiber* looper=xfiber->CreateFiber([&](){
        xfiber->EventLoop();
    },0,"looper");
    xfiber->WakeupFiber(looper);
    // if(xfiber->ready_fibers_.size()==2){
    //     cout<<"size erro"<<endl;
    //     exit(0);
    // }
    // if(xfiber->work_fibers_.size()<1000){
    //     cout<<"work error"<<endl;
    //     cout<<xfiber->work_fibers_.size()<<endl;
    //     exit(0);
    // }
    xfiber->Dispatch();

    return 0;
}
