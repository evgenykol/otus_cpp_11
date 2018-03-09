#include <iostream>
#include <thread>
#include "string.h"
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

void single_thread_test_1()
{
    char str1_1[] = "cmd1\n";
    char str1_2[] = "cmd2\ncmd3\n";
    char str1_3[] = "{\ncmd4\ncmd5\n";
    char str1_4[] = "cmd6\ncmd7\n}\n";
    char str1_5[] = "cmd8\n";

    char str2_1[] = "{\n";
    char str2_2[] = "cmd_1\n";
    char str2_3[] = "cmd_2\n";
    char str2_4[] = "{\ncmd_3\ncmd_4\n}\ncmd_5\ncmd_6\n}\n";

    auto h = async::connect(1);
    auto h2 = async::connect(2);

    async::receive(h, str1_1, strlen(str1_1));
    async::receive(h2, str2_1, strlen(str2_1));

    async::receive(h, str1_2, strlen(str1_2));
    async::receive(h2, str2_2, strlen(str2_2));

    async::receive(h, str1_3, strlen(str1_3));
    async::receive(h2, str2_3, strlen(str2_3));

    async::receive(h, str1_4, strlen(str1_4));
    async::receive(h2, str2_4, strlen(str2_4));

    async::receive(h, str1_5, strlen(str1_5));

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
    single_thread_test_1();
    //multi_thread_test();

    return 0;
}
