#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

long g_var = 0;

void *myFun(void *arg)
{
    long stop = *((long *)arg);
    long i;
    long *ret;

    i = -1;
    int loc;
    ret = (long *)malloc(sizeof(long));
    while(++i < stop)
        g_var++;
    return (NULL);
}

int main(int argc, char *argv[])
{
    pthread_t th1, th2;
    int res, loop;
    void *ret;

    loop = (argc > 1) ? atoi(argv[1]) : 100000;
    res = pthread_create(&th1, NULL, myFun, &loop);
    if (res != 0)
        return (0);
    res = pthread_create(&th2, NULL, myFun, &loop);
    if (res != 0)
        return (0);
    res = pthread_join(th1, &ret);
    if (res != 0)
        return (0);
    res = pthread_join(th2, &ret);
    if (res != 0)
        return (0);
    printf("glob = %ld\n", g_var);
    return(0);
}