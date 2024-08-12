#include "request.h"
#include "dispatcher.h"

#include <iostream>
#include <string>
#include <csignal>
#include <chrono>
#include <thread>

sig_atomic_t signal_caught = 0;
std::mutex logMutex;

void signal_handler(int sig) {
    signal_caught = 1;
}

void logFunc(std::string text) {
    logMutex.lock();
    std::cout << text << std::endl;
    logMutex.unlock();
}

int main() {
    signal(SIGINT, &signal_handler);
    Dispatcher::init(10);
    std::cout << "Initialised.\n";
    int cycles = 0;
    Request* rq = 0;
    while (!signal_caught && cycles < 50) {
        rq = new Request();
        rq->setValue(cycles);
        rq->setOutput(&logFunc);
        Dispatcher::addRequest(rq);
        cycles++;
    }
    std::this_thread::sleep_for(std::chrono::seconds(5));
    Dispatcher::stop();

    std::cout << "Clean up\n";

    return 0;
}
