#include <iostream>
#include <map>
#include <memory>
#include <mutex>

#include "async.h"
#include "bulk.h"

using namespace bulk;
namespace async {

std::map<int, std::unique_ptr<BulkContext>> bulk_contexts;
std::int64_t contexts_counter = 0;
std::mutex connect_mutex;
std::mutex recv_mutex;
std::mutex disconnect_mutex;

handle_t connect(std::size_t bulk)
{
    //std::cout << "connect, bulk size = " << bulk << std::endl;
    std::lock_guard<std::mutex> lock(connect_mutex);
    ++contexts_counter;
    bulk_contexts[contexts_counter] = std::make_unique<BulkContext>(bulk);
    return reinterpret_cast<handle_t>(contexts_counter);
}

void receive(handle_t handle, const char *data, std::size_t size)
{
    //std::cout << "receive, handle = " << handle << " size = " << size << std::endl;
    std::lock_guard<std::mutex> lock(recv_mutex);
    bulk_contexts[reinterpret_cast<std::int64_t>(handle)]->process_input(data, size);
}

void disconnect(handle_t handle)
{
    //std::cout << "disconnect, handle = " << handle << std::endl;
    std::lock_guard<std::mutex> lock(disconnect_mutex);
    auto p = bulk_contexts.find(reinterpret_cast<std::int64_t>(handle));
    if (p != bulk_contexts.end())
    {
        p->second->end_input();
        bulk_contexts.erase(p);
        //cout << "bulk_contexts.size() = " << bulk_contexts.size() << endl;
    }
}

}
