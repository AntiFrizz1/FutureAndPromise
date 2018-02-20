#pragma once

#include "future.h"
template<typename T>
class Promise {
private:
    std::shared_ptr<shared_state<T>> local_state;
    std::atomic_bool is_get;

public:
    Promise() : local_state(std::make_shared<shared_state<T>>()) {
        is_get = false;
        local_state->has_promise = true;
    }

    Promise(Promise<T> &&promsie) noexcept : local_state(move(promsie.local_state)) {
        is_get = promsie.is_get.load();
    }

    Promise &operator=(Promise<T> &&promise) noexcept {
        is_get = promise.is_get.load();
        local_state = move(promise.local_state);
        return *this;
    }

    ~Promise() {
        if(local_state) {
            local_state->has_promise = false;
            local_state->cv.notify_one();
        }
    }

    void set(const T & value) {
        std::unique_lock<std::mutex> lock(local_state->locker);
        if (local_state->is_ready) {
            throw std::runtime_error("value setted");
        }
        local_state->value = value;
        local_state->is_ready = true;
        local_state->cv.notify_one();
    }

    void set(T&& value) {
        std::unique_lock<std::mutex> lock(local_state->locker);
        if (local_state->is_ready) {
            throw std::runtime_error("value setted");
        }
        local_state->value = std::move(value);
        local_state->is_ready = true;
        local_state->cv.notify_one();
    }

    void set_exception(const std::exception_ptr & e) {
        std::unique_lock<std::mutex> lock(local_state->locker);
        if (local_state->error) {
            throw std::runtime_error("exception seted");
        }
        local_state->error = e;
        local_state->is_ready = true;
        local_state->cv.notify_one();
    }

    Future<T> get_future() {
        if (is_get) {
            throw std::runtime_error("Future setted");
        }
        is_get = true;
        return Future<T>(local_state);
    }

    void set_pool(ThreadPool * pool) {
        local_state->pool = pool;
    }
};

template<typename T>
class Promise<T &> {
private:
    std::shared_ptr<shared_state<T &>> local_state;
    std::atomic_bool is_get;

public:
    Promise() : local_state(std::make_shared<shared_state<T &>>()) {
        is_get = false;
        local_state->has_promise = true;
    }

    Promise(Promise &&promsie) : local_state(move(promsie.local_state)) {
        is_get = promsie.is_get.load();
    }

    Promise &operator=(Promise<T &> &&promise) {
        is_get = promise.is_get.load();
        local_state = move(promise.local_state);
        return *this;
    }

    Promise(const Promise &) = delete;
    Promise & operator=(const Promise &) = delete;

    ~Promise() {
        if(local_state) {
            local_state->has_promise = false;
            local_state->cv.notify_one();
        }
    }


    void set(T& value) {
        std::unique_lock<std::mutex> lock(local_state->locker);
        if (local_state->is_ready) {
            throw std::runtime_error("value setted");
        }
        local_state->value = &value;
        local_state->is_ready = true;
        local_state->cv.notify_one();
    }
    void set(T&& value) {
        std::unique_lock<std::mutex> lock(local_state->locker);
        if (local_state->is_ready) {
            throw std::runtime_error("value setted");
        }
        local_state->value = std::move(value);
        local_state->is_ready = true;
        local_state->cv.notify_one();
    }

    void set_exception(const std::exception_ptr & e) {
        std::unique_lock<std::mutex> lock(local_state->locker);
        if (local_state->error) {
            throw std::runtime_error("exception seted");
        }
        local_state->error = e;
        local_state->is_ready = true;
        local_state->cv.notify_one();
    }

    Future<T &> get_future() {
        if (is_get) {
            throw std::runtime_error("Future setted");
        }
        is_get = true;
        return Future<T &>(local_state);
    }

    void set_pool(ThreadPool * pool) {
        local_state->pool = pool;
    }
};

template<>
class Promise<void> {
private:
    std::shared_ptr<shared_state<void>> local_state;
    std::atomic_bool is_get;

public:
    Promise() : local_state(std::make_shared<shared_state<void>>()) {
        is_get = false;
        local_state->has_promise = true;
    }

    Promise(Promise<void> &&promsie) : local_state(move(promsie.local_state)) {
        is_get = promsie.is_get.load();
    }

    Promise &operator=(Promise<void> &&promise) {
        is_get = promise.is_get.load();
        local_state = move(promise.local_state);
        return *this;
    }

    Promise(Promise<void> const &) = delete;
    Promise & operator=(Promise<void> const &) = delete;

    ~Promise() {
        if(local_state) {
            local_state->has_promise = false;
            local_state->cv.notify_one();
        }
    }


    void set() {
        std::unique_lock<std::mutex> lock(local_state->locker);
        if (local_state->is_ready) {
            throw std::runtime_error("value setted");
        }
        local_state->is_ready = true;
        local_state->cv.notify_one();
    }

    void set_exception(const std::exception_ptr & e) {
        std::unique_lock<std::mutex> lock(local_state->locker);
        if (local_state->error) {
            throw std::runtime_error("exception seted");
        }
        local_state->error = e;
        local_state->is_ready = true;
        local_state->cv.notify_one();
    }

    Future<void> get_future() {
        if (is_get) {
            throw std::runtime_error("Future setted");
        }
        is_get = true;
        return Future<void>(local_state);
    }

    void set_pool(ThreadPool * pool) {
        local_state->pool = pool;
    }
};
