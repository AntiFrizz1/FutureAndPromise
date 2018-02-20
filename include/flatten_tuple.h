#pragma once
#include "promise.h"
#include <tuple>


template<typename T, typename Q = void>
struct get_type;


template<typename T>
struct get_type<T> {
    typedef T type_t;
};

template<typename T>
struct get_type<Future<T>> {
    typedef typename get_type<T>::type_t type_t;
};

template <typename ...Args>
struct get_type<std::tuple<Args...>> {
    typedef std::tuple<typename get_type<Args>::type_t...> type_t;
};

template<typename T>
T execute(const T &future) {
    return std::move(future);
}

template<typename T>
T execute(const Future<T> &future) {
    return std::move(execute(std::move(future.get())));
}

template<typename ...Args, std::size_t... I>
auto flatten_tuple_impl(const std::tuple<Args...>& a, std::index_sequence<I...>)
{
    return std::make_tuple(execute(std::get<I>(a))...);
}

template <typename ...TParams, typename indexx = std::make_index_sequence<sizeof...( TParams )>>
auto flatten_tuple(const std::tuple<TParams...> & tuple){
    std::shared_ptr<Promise<typename get_type<std::tuple<TParams...>>::type_t > > pointer (new Promise<typename get_type<std::tuple<TParams...>>::type_t >);
    if (ThreadPool::cur_pool != nullptr) {
        ThreadPool::cur_pool->execute([pointer, &tuple](){
            auto t = flatten_tuple_impl(tuple, indexx{});
            pointer->set(t);
        });
    } else {
        std::thread([pointer, &tuple]() {
            auto t = flatten_tuple_impl(tuple, indexx{});
            pointer->set(t);
        }).detach();
    }
    return pointer->get_future();
}
