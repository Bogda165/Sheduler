//
// Created by User on 12/08/2024.
//

#include "dispatcher.h"

#include <iostream>

std::queue<AbstractReuquest*> Dispatcher::requests;
std::queue<Worker*> Dispatcher::workers;
std::mutex Dispatcher::request_mtx;
std::mutex Dispatcher::worker_mtx;
std::vector<Worker*> Dispatcher::allWorkers;
std::vector<std::thread*> Dispatcher::threads;

bool Dispatcher::init(int workers_i) {
    std::thread* t = nullptr;
    Worker* w = nullptr;

    for(int i = 0; i < workers_i; i++) {
        w = new Worker;
        allWorkers.push_back(w);
        t = new std::thread(&Worker::run, w);
        threads.push_back(t);
    }
    return true;
}

bool Dispatcher::stop() {
    for (auto worker: allWorkers) {
        worker->stop();
    }
    std::cout << "Stoped all workers" << std::endl;
    for(auto thread: threads) {
        thread->join();
        std::cout << "Joined thread" << std::endl;
    }
}

void Dispatcher::addRequest(AbstractReuquest *request) {
    worker_mtx.lock();

    if(!workers.empty()) {
        Worker* worker = workers.front();
        worker->setRequest(request);
        std::condition_variable *cv;
        worker->getCondition(cv);
        cv->notify_one();
        workers.pop();
        worker_mtx.unlock();
    }else //else add request to a queue
    {
        worker_mtx.unlock();
        request_mtx.lock();
        requests.push(request);
        request_mtx.unlock();
    }
    //else add request to a queue
}

bool Dispatcher::addWorker(Worker *worker) {
    bool wait = true;
    request_mtx.lock();
    if(!requests.empty()) {
        AbstractReuquest* request = requests.front();
        worker->setRequest(request);
        requests.pop();
        wait = false;
        request_mtx.unlock();
    }else {
        request_mtx.unlock();
        worker_mtx.lock();
        workers.push(worker);
        worker_mtx.unlock();
    }

    return wait;
}