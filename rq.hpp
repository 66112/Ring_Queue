#ifndef __RQ_HPP__
#define __RQ_HPP__ 

#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <stdlib.h>

using namespace std;

class RingQueue
{
public:
    RingQueue(int num):_cap(num),arr(num)
    {
        sem_init(&blank_sem,0,_cap);  //初始空格为满
        sem_init(&data_sem,0,0);      //初始数据为0
        c_step = p_step = 0;          //初始下标为0
    }
    ~RingQueue()
    {
        sem_destroy(&blank_sem);
        sem_destroy(&data_sem);
    }
    void Push(const int& data)
    {
        P(blank_sem);            //申请一个格子
        arr[p_step] = data;
        V(data_sem);             //增加一个数据
        p_step++;
        p_step %= _cap;          //环形数组
    }
    void Pop(int &data)
    {
        P(data_sem);
        data = arr[c_step];
        V(blank_sem);
        c_step++;
        c_step %= _cap;
    }
private:
    void P(sem_t &sem)
    {
        sem_wait(&sem);   //等待信号量，将信号量的值减1
    }
    void V(sem_t &sem)
    {
        sem_post(&sem);   //释放信号量，将信号量的值加1
    }
private:
    vector<int> arr;      //数组
    int _cap;             //容量
 
    sem_t blank_sem;      //空格数
    sem_t data_sem;       //数据数

    int c_step;     //consums的下标
    int p_step;     //produce的下标
};

#endif 
