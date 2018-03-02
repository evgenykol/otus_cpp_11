#include <iostream>
#include <thread>
#include "async.h"

void single_thread_test()
{
    std::size_t bulk = 5;
    auto h = async::connect(bulk);
    auto h2 = async::connect(2);
    async::receive(h, "1", 1);
    async::receive(h2, "1\n", 2);
    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h2, "2\nq\nw\ne\nr\nt\ny\n", 14);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);
    async::receive(h2, "{\na\n", 4);
    async::disconnect(h);
    async::disconnect(h2);
}

void f1()
{
    std::size_t bulk = 5;
    auto h = async::connect(bulk);
    async::receive(h, "1", 1);
    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive(h, "b\nc\nd\n}\n89\n", 11);
    async::disconnect(h);
}

void f2()
{
    auto h2 = async::connect(2);
    async::receive(h2, "1\n", 2);
    async::receive(h2, "2\nq\nw\ne\nr\nt\ny\n", 14);
    async::receive(h2, "{\na\n", 4);
    async::disconnect(h2);
}

void multi_thread_test()
{
    std::thread t1(f1);
    std::thread t2(f2);

    t1.join();
    t2.join();
}

int main(int, char *[])
{
    //single_thread_test();
    multi_thread_test();

    return 0;
}
