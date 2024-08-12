//
// Created by User on 12/08/2024.
//

#ifndef SHEDULER_WORKER_H
#define SHEDULER_WORKER_H

#include "abstract_request.h"

#include <condition_variable>
#include <mutex>

class Worker {

    std::condition_variable cv;
    std::mutex mtx;
    std::unique_lock<std::mutex> ulock;

    AbstractReuquest* request;
    bool ready;
    bool running;

public:

    Worker();
    void run();
    void stop();
    void getCondition(std::condition_variable* &cv);
    void setRequest(AbstractReuquest* request);

};


#endif //SHEDULER_WORKER_H
