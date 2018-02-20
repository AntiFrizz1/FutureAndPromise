/*
#ifdef _GTEST

#include "flatten_tuple.h"

#include <gtest/gtest.h>

TEST(tuple, test_1) {
    Promise<int> promise;
    std::tuple<int, double, Future<int>, char> tuple = std::make_tuple(1, 1.1, promise.get_future(), 'q');

    auto res = FlattenTuple(tuple);

    promise.set(10);

    ASSERT_EQ(10, std::get<2>(res.get()));
}
#endif // _GTEST
*/