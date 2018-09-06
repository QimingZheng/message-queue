#include "queue_store.h"
#include<iostream>
#include <cstring>

using namespace std;
using namespace race2018;

/**
 * This in-memory implementation is for demonstration purpose only. You are supposed to modify it.
 */
void queue_store::put(const string& queue_name, const MemBlock& message) {
    //lock_guard<mutex> lock(mtx);
    
    map_mtx.lock();
    lock_guard<mutex> lock(mtx[queue_name]);
    if(queue_map.find(queue_name)==queue_map.end())
        {
            queue_map[queue_name].push_back(message);
            map_mtx.unlock();
            return;
        }
    map_mtx.unlock();
    
    queue_map[queue_name].push_back(message);
}

/**
 * This in-memory implementation is for demonstration purpose only. You are supposed to modify it.
 */
vector<MemBlock> queue_store::get(const std::string& queue_name, long offset, long number) {
    //lock_guard<mutex> lock(mtx);

    lock_guard<mutex> lock(mtx[queue_name]);

    if (queue_map.find(queue_name) == queue_map.end()) {
        return vector<MemBlock>();
    }
    auto queue = queue_map[queue_name];
    if (offset >= queue.size()) {
        return vector<MemBlock>();
    }
    vector<MemBlock> ret;
    //ret.insert(ret.end(),queue.begin()+offset, offset + number > queue.size() ? queue.end() : queue.begin() + offset + number);
     
    vector<MemBlock> searchResult(queue.begin() + offset,
                            offset + number > queue.size() ? queue.end() : queue.begin() + offset + number);

    // Return deep copy of the MemBlock such that benchmark tool may release MemBlock::ptr safely.
    for (const auto &item : searchResult) {
        MemBlock block;
        block.size = item.size;
        block.ptr = new char[block.size];
        memcpy(block.ptr, item.ptr, block.size);
        ret.push_back(block);
    }
    
    return ret;
}
