# include <iostream>
# include <semaphore.h>
# include <stdlib.h>
# include <unistd.h>
# define BUFFSIZE 100

using namespace std;

sem_t empty, full, mutex;
int buff[BUFFSIZE];
int index_=0;
void* consumer(void* arg){
    cout << "进入消费者线程" << endl;
    pthread_detach(pthread_self());
    while(true){
        cout << "消费者: 尝试进入缓冲区\n";
        sem_wait(&full);
        sem_wait(&mutex);
        cout << "消费者: 拿走一个资源: " << buff[index_] << ", 当前资源数: " << index_+1 << endl;
        buff[index_--] = 0;
        sem_post(&empty);
        sem_post(&mutex);
        sleep(0.5);
        if(index_ == 7) break;
    }
    pthread_exit(NULL);
}

void* server(void* arg){
    cout << "进入生产者线程" << endl;
    pthread_detach(pthread_self());
    while(true){
        cout << "生产者: 尝试进入缓冲区\n" << endl;
        sem_wait(&empty);
        sem_wait(&mutex);
        int val = rand();
        cout << "生产者: 生产一个资源: " << val << ", 当前资源数: " << index_+1 << endl;
        buff[++index_] = val;
        sem_post(&full);
        sem_post(&mutex);
        sleep(1);
        if(index_ == 9) break;
    }
    pthread_exit(NULL);
}




int main(){
    sem_init(&empty, 0, BUFFSIZE);  // int sem_init(sem_t *sem, int pshared, unsigned int value);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    pthread_t ct;
    pthread_t st;
    pthread_create(&ct, NULL, consumer, NULL);
    pthread_create(&st, NULL, server, NULL);
    pthread_exit(NULL);
}