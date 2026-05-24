#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define bufferSize 5

int in = 0;
int out = 0;
int buffer[bufferSize];
int count = 0;
int S = 1;
int n1 = 0;
int n2 = 0;

void wait()
{
  while (S <= 0)
    ;
  S--;
}
void signal()
{
  S++;
}

void *producer(void *arg)
{

  while (n1 < 10)
  {
    while ((in + 1) % bufferSize == out)
      ;
    wait();
    buffer[in] = ++count;
    printf("Producer produced:%d\n", buffer[in]);
    in = (in + 1) % bufferSize;
    n1++;
    sleep(1);
    signal();
  }
}
void *consumer(void *arg)
{

  while (n2 < 10)
  {
    while (in == out)
      ;
    wait();
    int op = buffer[out];
    printf("Consumer consumed:%d\n", buffer[out]);
    out = (out + 1) % bufferSize;
    n2++;
    sleep(1);
    signal();
  }
}
void main()
{
  pthread_t producerTh;
  pthread_t consumerTh;

  pthread_create(&producerTh, NULL, producer, NULL);
  pthread_create(&consumerTh, NULL, consumer, NULL);

  pthread_join(producerTh, NULL);
  pthread_join(consumerTh, NULL);
}