#include <iostream>
#include <map>
#include <memory>

#include "async.h"
#include "bulk.h"
namespace async {

std::map<int, std::unique_ptr<BulkContext>> bulk_contexts;
std::int64_t contexts_counter = 0;

handle_t connect(std::size_t bulk)
{
    std::cout << "connect, bulk size = " << bulk << std::endl;
    ++contexts_counter;
    bulk_contexts[contexts_counter] = std::make_unique<BulkContext>(bulk);
    return reinterpret_cast<handle_t>(contexts_counter);
}

void receive(handle_t handle, const char *data, std::size_t size)
{
    std::cout << "receive, handle = " << handle << " size = " << size << std::endl;
    bulk_contexts[reinterpret_cast<std::int64_t>(handle)]->processLine(data, size);
}

void disconnect(handle_t handle)
{
    std::cout << "disconnect, handle = " << handle << std::endl;
}

}
