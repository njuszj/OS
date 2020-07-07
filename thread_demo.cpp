# include <iostream>
# include <pthread.h>

using namespace std;

void* say_hello(void* arg){
    unsigned int tid = *((int*)arg);
    cout << ("Hello World " + to_string(tid) + "\n");
    pthread_exit(NULL);
}

int main(){
    pthread_t tids[10];
    int vals[10];
    for(int i=0; i<10; i++){
        vals[i] = i;
        int ret = pthread_create(&tids[i], NULL, say_hello, (void*)(&vals[i]));
        if(ret){
            cout << "Failed to create thread" << endl;
        }
    }
    // pthread_exit 用于显式地退出一个线程。通常情况下，pthread_exit() 函数是在线程完成工作后无需继续存在时被调用。
    // 如果 main() 是在它所创建的线程之前结束，并通过 pthread_exit() 退出，那么其他线程将继续执行。否则，它们将在 main() 结束时自动被终止。
    pthread_exit(NULL);
}