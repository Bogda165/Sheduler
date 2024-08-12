//
// Created by User on 12/08/2024.
//

#include "Worker.h"
#include "dispatcher.h"

Worker::Worker() {
    running = true;
    ready = false;
    ulock = std::unique_lock<std::mutex>(mtx);
}

void Worker::run() {
    while(running) {
        if(ready) {
            ready = false;
            request->process();
            request->finish();
        }
        if(Dispatcher::addWorker(this)) {
            if(!ready && running) {
                if (cv.wait_for(ulock, std::chrono::seconds(1)) == std::cv_status::timeout) {
                    //time out
                }
            }
        }
    }

}

void Worker::stop() {
    running = false;
}

void Worker::setRequest(AbstractReuquest *request) {
    this->request = request;
    ready = true;
}

void Worker::getCondition(std::condition_variable *&cv) {
    cv = &(this)->cv;
}

