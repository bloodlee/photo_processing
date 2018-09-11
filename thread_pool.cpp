//
// Created by yli on 9/10/2018.
//

#include "thread_pool.h"

void Worker::operator()() {
    pool.service.run();
}

ThreadPool::ThreadPool(size_t threads) : working(service) {
    for (size_t i = 0; i < threads; ++i) {
        workers.push_back(
                std::unique_ptr<boost::thread>(
                        new boost::thread(Worker(*this))
                )
        );
    }
}

// the destructor joins all threads
ThreadPool::~ThreadPool()
{
    service.stop();

    for(auto i = 0; i < workers.size(); ++i) {
        workers[i]->join();
    }
}