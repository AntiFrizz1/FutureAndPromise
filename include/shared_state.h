#pragma once

#include <mutex>
#include <condition_variable>
#include <atomic>
#include "thread_pool.h"

template <typename> class Promise;
template <typename> class Future;

template<typename T>
class shared_state {
private:
    T value;
    std::atomic_bool is_ready;
    std::atomic_bool has_promise;
    std::exception_ptr error;
    std::mutex locker;
    std::condition_variable cv;
    ThreadPool * pool = nullptr;
public:
    friend class Promise<T>;
    friend class Future<T>;
};

template<typename T>
class shared_state<T &> {
private:
    T *value;
    std::atomic_bool is_ready;
    std::atomic_bool has_promise;
    std::exception_ptr error;
    std::mutex locker;
    std::condition_variable cv;
    ThreadPool * pool = nullptr;
public:
    friend class Promise<T &>;
    friend class Future<T &>;
};

template<>
class shared_state<void> {
private:
    std::atomic_bool is_ready;
    std::atomic_bool has_promise;
    std::exception_ptr error;
    std::mutex locker;
    std::condition_variable cv;
    ThreadPool * pool = nullptr;
public:
public:
    friend class Promise<void>;
    friend class Future<void>;
};
