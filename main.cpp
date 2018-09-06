#include <iostream>
#include <cstring>
#include <thread>
#include "queue_store.h"

using namespace std;
using namespace race2018;

#define THREAD_NUM 1000
#define MSG_NUM 15000
#define QUE_NUM 200

void put_get(int tid, queue_store &store){
    
    const string quename = "Queue-" + to_string(tid%QUE_NUM);
    for (int i = 0; i < MSG_NUM; i++) {
        string slogan = string("abcdefghijklmnopqrst+abcdefghijklmnopqrst+abcdefghijklm") + to_string(i);
        char* data = new char[slogan.size() + 1];
        strcpy(data, slogan.c_str());
        MemBlock msg = {static_cast<void*>(data),
                        static_cast<size_t>(sizeof(data))//slogan.size()+1)
        };
        store.put(quename, msg);
    }

     vector<MemBlock> list = store.get(quename, 10, 500);
    /*
    for (MemBlock &item : list) {
        char* msg = static_cast<char *>(item.ptr);
        cout << msg << endl;
    }
    */
//    cout<< "Thread " << tid << " Done!\n";
}


int main(int argc, char* argv[]) {

    queue_store store;

    std::thread t[THREAD_NUM];
    for (int i=0;i<THREAD_NUM;i++)
        t[i] = std::thread(put_get, i, std::ref(store));
    
    for (int i=0;i<THREAD_NUM;i++)
        t[i].join();
    return 0;
}
