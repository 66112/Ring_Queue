#include "rq.hpp"
const int num = 10;

void* produce_routine(void* arg)
{
    RingQueue* rqp = (RingQueue*)arg;
    srand((unsigned long)time(NULL));
    for(; ; )
    {
        sleep(1);
        int data = rand()%50+1;
        rqp->Push(data);
        cout << "produce_routine... data: " << data << endl;
    }
}
void* consums_routine(void* arg)
{
    RingQueue* rpq = (RingQueue*)arg;
    for(; ; )
    {
        int data;
        rpq->Pop(data);
        cout << "consums_routine... data: " << data << endl;
    }
}
int main()
{
    RingQueue* rqp = new RingQueue(num);
    pthread_t t1, t2;
    pthread_create(&t1,NULL,produce_routine,(void*)rqp);  //把环形队列传进去
    pthread_create(&t2,NULL,consums_routine,(void*)rqp);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    delete rqp;
    return 0;
}
