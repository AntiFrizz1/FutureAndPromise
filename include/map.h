#pragma once

#include "promise.h"

template <typename T, typename F>
Future<typename std::result_of<F(T)>::type> map(Future<T> &&future, const F &func) {
    std::shared_ptr<Promise<typename std::result_of<F(T)>::type>> p = std::shared_ptr<Promise<typename std::result_of<F(T)>::type>>(new Promise<typename std::result_of<F(T)>::type>());
    ThreadPool *pool = nullptr;
    if (future.get_pool() != nullptr) {
        pool = future.get_pool();
    } else if (ThreadPool::cur_pool != nullptr) {
        pool = ThreadPool::cur_pool;
    }
    if (pool != nullptr) {
        pool->execute([&future, &func, p]{
            p->set(std::move(func(future.get())));
        });
    } else {
        std::thread([&future, &func, p] {
            p->set(std::move(func(future.get())));
        }).detach();
    }
    return std::move(p->get_future());
};