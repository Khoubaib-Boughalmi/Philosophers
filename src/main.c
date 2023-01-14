#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_PHILO 5

int g_var = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void    *philosopher(void *arg)
{
    pthread_mutex_lock(&mutex);
    printf("PHILOS NUMBER #%d SAYS HI\n", g_var);
    g_var++;
    pthread_mutex_unlock(&mutex);
    return (NULL);
}

int ft_init_philos(int nop)
{
    int         i;
    int         res;
    pthread_t   *pth_lst;

    i = 0;
    pth_lst = (pthread_t *)malloc(nop * sizeof(pthread_t));
    if(!pth_lst)
        return (0);
    while (i < nop)
    {
        res = pthread_create(pth_lst + i, NULL, philosopher, NULL);
        if(res)
            return (0);
        i++;
    }
        i = 0;
    while (i < nop)
    {
        res = pthread_join(pth_lst[i], NULL);
        if(res)
            return (0);
        i++;
    }
    return (1);
}

int ft_init_mutexes(int nop)
{
    int             i;
    int             res;
    pthread_mutex_t *pth_mutex;
   
    i = 0;
    pth_mutex = (pthread_mutex_t *)malloc(nop * sizeof(pthread_mutex_t));
    if(!pth_mutex)
        return (0);
    while (i < nop)
    {
        res = pthread_mutex_init(pth_mutex + i, NULL);
        if(res)
            return (0);
        i++;
    }
    return (1);
}

int *ft_init_forks(int nop)
{
    int i;
    int *forks;

    i = 0;
    forks = (int *)malloc(nop * sizeof(int));
    if(!forks)
        return (0);
    while (i < nop)
    {
        forks[i] = 0;
        i++;
    }
    return (forks);
}


int main(int argc, char *argv[])
{
    if(!ft_init_philos(NUM_PHILO) || ! ft_init_mutexes(NUM_PHILO) || ft_init_forks(NUM_PHILO))
        return (0);
    printf("PHILOS AND MUTEXES CREATED SUCCESSFULLY\n");
    return (0);
}