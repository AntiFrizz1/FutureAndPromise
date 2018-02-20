#pragma once

#include "shared_state.h"
template<typename>
class Promise;

template<typename T>
class Future {
private:
    std::shared_ptr<shared_state<T>> local_state;

public:
    Future(std::shared_ptr<shared_state<T>> state) : local_state(state) {}

    Future(Future<T> &&f) : local_state(move(f.local_state)) {}

    Future &operator=(Future<T> &&f) {
        local_state = (std::move(f.local_state));
        return *this;
    }

    ThreadPool * get_pool() {
        return local_state->pool;
    }

    Future(Future const &) = delete;

    Future &operator=(Future const &) = delete;


    Future() {
        local_state = nullptr;
    }

    ~Future() {}

    T const &get() const;

    void wait() const;

    bool is_ready() const;

    friend class Promise<T>;
};

template<typename T>
T const &Future<T>::get() const {
    wait();
    if (local_state->error) {
        std::rethrow_exception(local_state->error);
    } else if (!local_state->has_promise && !is_ready()) {
        throw std::runtime_error("No promise");
    } else {
        return local_state->value;
    }
}

template<typename T>
void Future<T>::wait() const {
    std::unique_lock<std::mutex> lock(local_state->locker);
    if (is_ready()) {
        return;
    }
    while (!is_ready() && local_state->has_promise) {
        local_state->cv.wait(lock);
    }
}

template<typename T>
bool Future<T>::is_ready() const {
    return local_state->is_ready;
}
//&

template<typename T>
class Future<T &> {
private:
    std::shared_ptr<shared_state<T &>> local_state;

private:
    Future(std::shared_ptr<shared_state<T &>> state) : local_state(state) {}

public:
    Future() {
        local_state = nullptr;
    }
    Future(Future &&f) : local_state(move(f.local_state)) {}

    Future &operator=(Future &&f) {
        local_state = (std::move(f.local_state));
        return *this;
    }

    ThreadPool * get_pool() {
        return local_state->pool;
    }

    Future(Future const &) = delete;

    Future &operator=(Future const &) = delete;

    ~Future() {}

    T &get() const;

    void wait() const;

    bool is_ready() const;

    friend class Promise<T &>;
};

template<typename T>
T &Future<T &>::get() const {
    wait();
    if (local_state->error) {
        std::rethrow_exception(local_state->error);
    } else if (!local_state->has_promise && !is_ready()) {
        throw std::runtime_error("No promise");
    } else {
        return *local_state->value;
    }
}

template<typename T>
void Future<T &>::wait() const {
    std::unique_lock<std::mutex> lock(local_state->locker);
    if (is_ready()) {
        return;
    }
    while (!is_ready() && local_state->has_promise) {
        local_state->cv.wait(lock);
    }
}

template<typename T>
bool Future<T &>::is_ready() const {
    return local_state->is_ready;
}
//void

template<>
class Future<void> {
private:
    std::shared_ptr<shared_state<void>> local_state;

private:
    Future(std::shared_ptr<shared_state<void>> state)
            : local_state(state) {}

public:
    Future() {
        local_state = nullptr;
    }
    Future(Future &&f) : local_state(move(f.local_state)) {}

    Future &operator=(Future &&f) {
        local_state = (std::move(f.local_state));
        return *this;
    }

    ThreadPool * get_pool() {
        return local_state->pool;
    }

    Future(Future const &) = delete;

    Future &operator=(Future const &) = delete;

    ~Future() {}

    void get() const;

    void wait() const;

    bool is_ready() const;

    friend class Promise<void>;
};

void Future<void>::get() const {
    wait();
    if (local_state->error) {
        std::rethrow_exception(local_state->error);
    } else if (!local_state->has_promise && !is_ready()) {
        throw std::runtime_error("No promise");
    }
}

void Future<void>::wait() const {
    std::unique_lock<std::mutex> lock(local_state->locker);
    if (is_ready()) {
        return;
    }
    while (!is_ready() && local_state->has_promise) {
        local_state->cv.wait(lock);
    }
}

bool Future<void>::is_ready() const {
    return local_state->is_ready;
}
