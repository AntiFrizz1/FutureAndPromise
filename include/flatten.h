#pragma once
#include <thread>
#include "promise.h"
#include "future.h"
template <typename T>
struct get_type_inc;

template<typename T>
struct get_type_inc<Future<T>> {
    typedef T type_inc;
};

template<typename T>
struct get_type_inc<Future<Future<T>>> {
    typedef typename get_type_inc<Future<T>>::type_inc type_inc;
};

template<typename T>
auto flatten_impl(const Future<T> &future) {
    return std::move(future.get());
}

template<typename T>
auto flatten_impl(const Future<Future<T>> &future) {
    return std::move(flatten_impl(std::move(future.get())));
}


template<typename T>
auto flatten(const Future<Future<T>> &future) {
    std::shared_ptr<Promise<typename get_type_inc<Future<T>>::type_inc>> pointer(new Promise<typename get_type_inc<Future<T>>::type_inc>());
    if (ThreadPool::cur_pool != nullptr) {
        ThreadPool::cur_pool->execute([&future, pointer]() {
            pointer->set(std::move(flatten_impl(std::move(future))));
        });
    } else {
        std::thread([&future, pointer]() {
            pointer->set(std::move(flatten_impl(std::move(future))));
        }).detach();
    }
    return std::move(pointer->get_future());
}

template<typename T>
auto flatten(Future<T> future) {
    return std::move(future);
}


template<template<typename, typename...> class C, typename T>
Future<C<T>> flatten(C<Future<T>> const &col) {
    std::shared_ptr<Promise<C<T>>> pointer(new Promise<C<T>>());
    std::thread([pointer, &col]() {
        C<T> output = C<T>();
        for (const Future<T> &future : col) {
            output.insert(std::end(output), future.get());
        }
        pointer->set(output);
    }).detach();
    return pointer->get_future();
}