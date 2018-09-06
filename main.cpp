#include <iostream>
#include <cstring>
#include <thread>
#include<time.h>
#include "queue_store.h"

using namespace std;
using namespace race2018;

#define THREAD_NUM 24
#define MSG_NUM 600000
#define QUE_NUM 10000

void put_get(int tid, queue_store &store){
    
    //const string quename = "Queue-" + to_string(tid%QUE_NUM);
    for (int i = 0; i < MSG_NUM; i++) {
        string quename = "Queue-" + to_string(tid) + to_string(rand()%(QUE_NUM/THREAD_NUM));
        string slogan = string("abcdefghijklmnopqrst+abcdefghijklmnopqrst+abcdefghijklm") + to_string(i);
        char* data = new char[slogan.size() + 1];
        strcpy(data, slogan.c_str());
        MemBlock msg = {static_cast<void*>(data),
                        static_cast<size_t>(sizeof(data))//slogan.size()+1)
        };
        store.put(quename, msg);
    }
/*
    for (int i = 0; i < 1000000/THREAD_NUM; i++){
    
         vector<MemBlock> list = store.get("Queue-" + to_string(tid) + "-0", 1, 2);
    
    }
*/
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
