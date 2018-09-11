//
// Created by yli on 9/10/2018.
//

#ifndef PHOTO_PROCESSING_THREAD_POOL_H
#define PHOTO_PROCESSING_THREAD_POOL_H

#include <vector>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <memory>

class ThreadPool;

class Worker {
public:
    Worker(ThreadPool &s) : pool(s) {}
    void operator()();
private:
    ThreadPool & pool;
};

class ThreadPool {
public:
    ThreadPool(size_t);

    template<class F> void enqueue(F f);

    ~ThreadPool();

private:
    std::vector<std::unique_ptr<boost::thread>> workers;

    boost::asio::io_service service;
    boost::asio::io_service::work working;

    friend class Worker;
};

template<class F>
void ThreadPool::enqueue(F f)
{
    service.post(f);
}

#endif //PHOTO_PROCESSING_THREAD_POOL_H
