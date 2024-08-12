//
// Created by User on 12/08/2024.
//

#ifndef SHEDULER_DISPATCHER_H
#define SHEDULER_DISPATCHER_H

#include "abstract_request.h"
#include "Worker.h"

#include <queue>
#include <mutex>
#include <thread>
#include <vector>

class Dispatcher {
    static std::queue<AbstractReuquest*> requests;
    static std::queue<Worker*> workers;
    static std::mutex worker_mtx;
    static std::mutex request_mtx;

    static std::vector<Worker*> allWorkers;
    static std::vector<std::thread*> threads;

public:
    static bool init(int workers);
    static bool stop();
    static bool addWorker(Worker* worker);
    static void addRequest(AbstractReuquest* request);
};


#endif //SHEDULER_DISPATCHER_H
