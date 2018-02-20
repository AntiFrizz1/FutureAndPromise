//
// Created by antifrizz on 20.01.18.
//
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#pragma once
class ThreadPool {
private:

    std::queue<std::function<void()>> functions;
    std::mutex data;
    std::condition_variable cv;
    std::atomic<bool> on;
    std::vector<std::thread> threads;
    int numOfThreads;

    void worker() {
        cur_pool = this;
        while (on) {
            std::function<void()> fn;
            {

                std::unique_lock<std::mutex> locker(data);
                cv.wait(locker, [&]() { return (!on || !functions.empty()); });
                if (functions.empty()) {
                    break;
                }
                fn = functions.front();
                functions.pop();
            }
            fn();
        }
    }

public:

    ThreadPool(int numberOfThreads) {
        on = true;
        for (int i = 0; i < numberOfThreads; i++) {
            threads.push_back(std::thread(&ThreadPool::worker, this));
        }
        numOfThreads = threads.size();
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> locker(data);
            on = false;
        }
        cv.notify_all();
        for (int i = 0; i < numOfThreads; i++) {
            threads[i].join();
        }
    }

    void execute(std::function<void()> const & fn) {
        {
            std::unique_lock<std::mutex> locker(data);
            functions.push(fn);
        }
        cv.notify_one();
    }
    static thread_local ThreadPool * cur_pool;
};

thread_local ThreadPool * ThreadPool::cur_pool = nullptr;