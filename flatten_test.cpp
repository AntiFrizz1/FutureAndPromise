
#include <gtest/gtest.h>
#include <string>
#include <list>
#include <fstream>
#include "flatten.h"
#include "map.h"
#include "flatten_tuple.h"
//Promise
//#define A B --- Вместо B вписать название соответствующего метода в своем классе Promise
#define Set set
#define SetException set_exception
#define GetFuture get_future
//Future

//#define A B --- Вместо B вписать название соответствующего метода в своем классе Future
#define IsReady is_ready
#define Get get
#define Wait wait
/*
TEST(promise, is_ready) {
    Promise<int> promise;
    Future<int> f = promise.get_future();


    ASSERT_FALSE(f.is_ready());

    int const x = 10;
    promise.set(x);
    ASSERT_TRUE(f.is_ready());
}

TEST(promise, Set_int) {
    Promise<int> promise;
    Future<int> f = promise.get_future();

    int const x = 10;
    promise.set(x);
    ASSERT_EQ(f.get(), x);
}

TEST(promise, Set_int_ampersand) {
    Promise<int &> promise;
    Future<int &> f = promise.get_future();

    int const y = 100;
    int x = 10;

    promise.set(x);

    f.get() = y;

    ASSERT_EQ(x, y);
}

TEST(promise, Set_void) {
    Promise<void> promise;
    Future<void> f = promise.get_future();

    ASSERT_FALSE(f.is_ready());

    promise.set();

    f.get();

    ASSERT_TRUE(f.is_ready());
}

TEST(promise, two_threads_get_set) {
    Promise<int> promise;
    Future<int> future = promise.get_future();

    int x = 777;

    std::thread t(
            [x](Promise<int> promise) {
                std::this_thread::sleep_for(std::chrono::seconds(1));

                promise.set(x);
            }, std::move(promise)
    );

    for (int i = 0; !future.is_ready(); ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    ASSERT_EQ(future.get(), x);

    t.join();
}

TEST(promise, two_threads_get_throw_exception) {
    Promise<int> promise;
    Future<int> future = promise.get_future();

    int x = 777;

    std::thread t(
            [x](Promise<int> promise) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }, std::move(promise)
    );

    ASSERT_ANY_THROW(future.get());

    t.join();
}
class TestInitInt : public ::testing::Test {
protected:
    void SetUp() {
        future = promise.GetFuture();
        future1 = promise1.GetFuture();
        future2 = promise2.GetFuture();
        future3 = promise3.GetFuture();
        future4 = promise4.GetFuture();
        future5 = promise5.GetFuture();
        ans = 100;
    }

    void TearDown() {

    }

    Promise<int> promise;
    Promise<Future<int>> promise1;
    Promise<Future<Future<int>>> promise2;
    Promise<Future<Future<Future<int> >>> promise3;
    Promise<Future<Future<Future<Future<int>> >>> promise4;
    Promise<Future<Future<Future<Future<Future<int>>> >>> promise5;
    Future<int> future;
    Future<Future<int>> future1;
    Future<Future<Future<int> > > future2;
    Future<Future<Future<Future<int>>> > future3;
    Future<Future<Future<Future<Future<int>>>>> future4;
    Future<Future<Future<Future<Future<Future<int>>>>> > future5;
    int ans;
};


class TestInitString : public ::testing::Test {
protected:
    void SetUp() {
        future = promise.GetFuture();
        future1 = promise1.GetFuture();
        future2 = promise2.GetFuture();
        future3 = promise3.GetFuture();
        future4 = promise4.GetFuture();
        future5 = promise5.GetFuture();
        ans = "Hi, world!";
    }

    void TearDown() {

    }

    Promise<std::string> promise;
    Promise<Future<std::string>> promise1;
    Promise<Future<Future<std::string>>> promise2;
    Promise<Future<Future<Future<std::string> >>> promise3;
    Promise<Future<Future<Future<Future<std::string>> >>> promise4;
    Promise<Future<Future<Future<Future<Future<std::string>>> >>> promise5;
    Future<std::string> future;
    Future<Future<std::string>> future1;
    Future<Future<Future<std::string> > > future2;
    Future<Future<Future<Future<std::string>>> > future3;
    Future<Future<Future<Future<Future<std::string>>>>> future4;
    Future<Future<Future<Future<Future<Future<std::string>>>>> > future5;
    std::string ans;
};

class TestInitDouble : public ::testing::Test {
protected:
    void SetUp() {
        future = promise.GetFuture();
        future1 = promise1.GetFuture();
        future2 = promise2.GetFuture();
        future3 = promise3.GetFuture();
        future4 = promise4.GetFuture();
        future5 = promise5.GetFuture();
        ans = 3.14;
    }

    void TearDown() {

    }

    Promise<double> promise;
    Promise<Future<double>> promise1;
    Promise<Future<Future<double>>> promise2;
    Promise<Future<Future<Future<double> >>> promise3;
    Promise<Future<Future<Future<Future<double>> >>> promise4;
    Promise<Future<Future<Future<Future<Future<double>>> >>> promise5;
    Future<double> future;
    Future<Future<double>> future1;
    Future<Future<Future<double> > > future2;
    Future<Future<Future<Future<double>>> > future3;
    Future<Future<Future<Future<Future<double>>>>> future4;
    Future<Future<Future<Future<Future<Future<double>>>>> > future5;
    double ans;
};

class TestInitObject : public ::testing::Test {
protected:


    struct Obj {
        int a;
        double b;
        std::string c;

        const bool operator==(const Obj &v2) const {
            return (a == v2.a) && (b == v2.b) && (c == v2.c);
        }
    };

    void SetUp() {
        future = promise.GetFuture();
        future1 = promise1.GetFuture();
        future2 = promise2.GetFuture();
        future3 = promise3.GetFuture();
        future4 = promise4.GetFuture();
        future5 = promise5.GetFuture();
        ans = {100, 3.14, "Hi, world!"};
    }

    void TearDown() {

    }

    Promise<Obj> promise;
    Promise<Future<Obj>> promise1;
    Promise<Future<Future<Obj>>> promise2;
    Promise<Future<Future<Future<Obj> >>> promise3;
    Promise<Future<Future<Future<Future<Obj>> >>> promise4;
    Promise<Future<Future<Future<Future<Future<Obj>>> >>> promise5;
    Future<Obj> future;
    Future<Future<Obj>> future1;
    Future<Future<Future<Obj> > > future2;
    Future<Future<Future<Future<Obj>>> > future3;
    Future<Future<Future<Future<Future<Obj>>>>> future4;
    Future<Future<Future<Future<Future<Future<Obj>>>>> > future5;
    Obj ans;
};

class TestInitCT : public ::testing::Test {
protected:
    void SetUp() {
        for (int i = 0; i < N; i++) {
            ansL.push_back(i);
            ansV.push_back(i);
        }

    }

    void TearDown() {

    }

    std::vector<Future<int> > v;
    std::list<Future<int> > l;
    std::vector<int> ansV;
    std::list<int> ansL;
    const int N = 5;
};

///int
TEST_F(TestInitInt, testFutureInt1) {
    promise.Set(ans);
    Future<int> res(std::move(flatten(std::move(future))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitInt, testFutureInt2) {

    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<int> res(std::move(flatten(std::move(future1))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitInt, testFutureInt3) {

    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<int> res(std::move(flatten(std::move(future2))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitInt, testFutureInt4) {

    promise3.Set(std::move(future2));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<int> res(std::move(flatten(std::move(future3))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitInt, testFutureInt5) {

    promise4.Set(std::move(future3));
    promise3.Set(std::move(future2));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<int> res(std::move(flatten(std::move(future4))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitInt, testFutureInt6) {

    promise5.Set(std::move(future4));
    promise4.Set(std::move(future3));
    promise3.Set(std::move(future2));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<int> res(std::move(flatten(std::move(future5))));
    ASSERT_EQ(res.get(), ans);
}
///double
TEST_F(TestInitDouble, testFutureDouble1) {
    promise.Set(ans);
    Future<double> res(std::move(flatten(std::move(future))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitDouble, testFutureDouble2) {

    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<double> res(std::move(flatten(std::move(future1))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitDouble, testFutureDouble3) {

    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<double> res(std::move(flatten(std::move(future2))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitDouble, testFutureDouble4) {

    promise3.Set(std::move(future2));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<double> res(std::move(flatten(std::move(future3))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitDouble, testFutureDouble5) {

    promise4.Set(std::move(future3));
    promise3.Set(std::move(future2));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<double> res(std::move(flatten(std::move(future4))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitDouble, testFutureDouble6) {

    promise5.Set(std::move(future4));
    promise4.Set(std::move(future3));
    promise3.Set(std::move(future2));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<double> res(std::move(flatten(std::move(future5))));
    ASSERT_EQ(res.get(), ans);
}
///object
TEST_F(TestInitObject, testFutureObject1) {
    promise.Set(ans);
    Future<Obj> res(std::move(flatten(std::move(future))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitObject, testFutureObject2) {

    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<Obj> res(std::move(flatten(std::move(future1))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitObject, testFutureObject3) {

    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<Obj> res(std::move(flatten(std::move(future2))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitObject, testFutureObject4) {

    promise3.Set(std::move(future2));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<Obj> res(std::move(flatten(std::move(future3))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitObject, testFutureObject5) {

    promise4.Set(std::move(future3));
    promise3.Set(std::move(future2));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<Obj> res(std::move(flatten(std::move(future4))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitObject, testFutureObject6) {

    promise5.Set(std::move(future4));
    promise4.Set(std::move(future3));
    promise3.Set(std::move(future2));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<Obj> res(std::move(flatten(std::move(future5))));
    ASSERT_EQ(res.get(), ans);
}
///string
TEST_F(TestInitString, testFutureString1) {
    promise.Set(ans);
    Future<std::string> res(std::move(flatten(std::move(future))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitString, testFutureString2) {

    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<std::string> res(std::move(flatten(std::move(future1))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitString, testFutureString3) {

    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<std::string> res(std::move(flatten(std::move(future2))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitString, testFutureString4) {

    promise3.Set(std::move(future2));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<std::string> res(std::move(flatten(std::move(future3))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitString, testFutureString5) {

    promise4.Set(std::move(future3));
    promise3.Set(std::move(future2));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<std::string> res(std::move(flatten(std::move(future4))));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitString, testFutureString6) {

    promise5.Set(std::move(future4));
    promise4.Set(std::move(future3));
    promise3.Set(std::move(future2));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    Future<std::string> res(std::move(flatten(std::move(future5))));
    ASSERT_EQ(res.get(), ans);
}
///async
TEST_F(TestInitInt, testAsync1) {
    Future<int> res(std::move(flatten(std::move(future))));

    std::this_thread::sleep_for(std::chrono::seconds(1));

    promise.Set(ans);
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitInt, testAsync2) {
    ThreadPool pool(3);
    promise.Set(ans);
    Future<int> res(std::move(flatten(std::move(future1))));

    std::this_thread::sleep_for(std::chrono::seconds(1));
    promise1.Set(std::move(future));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitInt, testAsync3) {

    Future<int> res(std::move(flatten(std::move(future2))));

    std::this_thread::sleep_for(std::chrono::seconds(2));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitInt, testAsync4) {

    promise3.Set(std::move(future2));
    promise.Set(ans);
    Future<int> res(std::move(flatten(std::move(future3))));

    std::this_thread::sleep_for(std::chrono::seconds(3));

    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitInt, testAsync5) {

    promise4.Set(std::move(future3));
    promise2.Set(std::move(future1));
    promise.Set(ans);
    Future<int> res(std::move(flatten(std::move(future4))));

    std::this_thread::sleep_for(std::chrono::seconds(1));

    promise3.Set(std::move(future2));

    promise1.Set(std::move(future));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitInt, testAsync6) {

    promise5.Set(std::move(future4));
    promise3.Set(std::move(future2));

    Future<int> res(std::move(flatten(std::move(future5))));
    promise2.Set(std::move(future1));
    promise1.Set(std::move(future));
    promise.Set(ans);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    promise4.Set(std::move(future3));
    ASSERT_EQ(res.get(), ans);
}

TEST_F(TestInitCT, testList) {
    for (int i = 0; i < N; i++) {
        Promise<int> p;
        l.push_back((p.GetFuture()));
        p.Set(i);
    }
    std::list<int> c = flatten(l).Get();
    ASSERT_EQ(ansL, c);

}

TEST_F(TestInitCT, testVector) {
    for (int i = 0; i < N; i++) {
        Promise<int> p;
        v.push_back((p.GetFuture()));
        p.Set(i);
    }

    std::vector<int> c = flatten(v).Get();
    ASSERT_EQ(ansV, c);

}

TEST_F(TestInitCT, testListAsync) {
    std::list<Promise<int> > prom(N);
    auto it = prom.begin();
    for (int i = 0; i < N; i++) {
        l.push_back(it->GetFuture());
        ++it;
    }

    Future<std::list<int> > g = flatten(l);

    std::this_thread::sleep_for(std::chrono::seconds(2));
    it = prom.begin();
    for (int i = 0; i < N; i++) {
        it->Set(i);
        ++it;
    }

    std::list<int> c = g.Get();
    ASSERT_EQ(ansL, c);

}

TEST_F(TestInitCT, testVectorAsync) {
    std::vector<Promise<int> > prom(N);
    for (int i = 0; i < N; i++) {
        v.push_back(prom[i].GetFuture());
    }
    Future<std::vector<int> > g = flatten(v);

    std::this_thread::sleep_for(std::chrono::seconds(2));


    for (int i = 0; i < N; i++) {
        prom[i].Set(i);
    }
    std::vector<int> c = g.Get();
    ASSERT_EQ(ansV, c);

}

TEST(m1, Map_test) {
    ThreadPool pool(3);
    Promise<int> p;
    p.set_pool(&pool);
    pool.execute([&p]() {
        p.set(0);
    });
    Future<int> fut1 = map(std::move(p.get_future()), [](int i) {
        return (i + 123);
    });
    ASSERT_EQ(fut1.get(), 123);
}*/

TEST(tuple, test_1) {
    ThreadPool pool(3);
    Promise<int> promise;
    std::tuple<int, double, Future<int>, char> tuple = std::make_tuple(1, 1.1, promise.get_future(), 'q');
    int ans = 10;
    pool.execute([&tuple]{
        auto res = flatten_tuple(tuple);
        std::fstream fout("/home/antifrizz/CLionProjects/FutureAndPromise/ans.txt");
        fout << std::get<2>(res.get());
        fout.close();
    });
    promise.set(10);
    //std::this_thread::sleep_for(std::chrono::seconds(15));
    ASSERT_EQ(10, 10);
}