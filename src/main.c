/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:30:12 by kboughal          #+#    #+#             */
/*   Updated: 2023/01/14 17:42:19 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosphers.h"

#define NUM_PHILO 5

int g_var = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void    *philosopher(void *arg)
{
    int i;
    t_philosopher philo;

    i = 0;
    while (1)
    {
        pthread_mutex_lock(&(((t_philosopher *)arg)[i].pth_mutex[i]));
        philo = ((t_philosopher *)arg)[i];
        if (!philo.forks[philo.right])
        {
            printf("philo %d says 9lawi\n", i);
            philo.forks[philo.right] = 1;
        }
        sleep(2);
        pthread_mutex_unlock(&((t_philosopher *)arg)[i].pth_mutex[i]);
        i++;
    }

    return (NULL);
}

int ft_init_philos(int nop, pthread_mutex_t *mutex, t_in *u_in, int *forks)
{
    int             i;
    int             res;
    t_philosopher   *philo;

    i = 0;
    philo = (t_philosopher *)malloc(nop * sizeof(t_philosopher));
    if(!philo)
        return (0);
    while (i < nop)
    {
        philo[i].id = i;
        philo[i].pth_mutex = mutex;
        philo[i].left= i;
        philo[i].right = (i + 1) % nop;
        philo[i].forks= forks;
        philo[i].u_in= u_in;
        res = pthread_create(&(philo[i].philo_thr), NULL, philosopher, (void *)philo);
        if(res)
            return (0);
        i++;
    }
    i = 0;
    while (i < nop)
    {
        res = pthread_join(philo[i].philo_thr, NULL);
        if(res)
            return (0);
        i++;
    }
    return (1);
}

int ft_init_mutexes(int nop, pthread_mutex_t *pth_mutex)
{
    int             i;
    int             res;
   
    i = 0;
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

int *ft_init_forks(int nop, int *forks)
{

    int i;

    i = 0;
    if(!forks)
        return (0);
    while (i < nop)
    {
        forks[i] = 0;
        i++;
    }
    return (forks);
}

int check_args(int argc, char *argv[], t_in *u_in)
{
    int i;

    if (argc < 5 || argc > 6 )
        return (0);
    i = 1;
    while (i < argc)
    {
        if(ft_atoi(argv[i]) <= 0)
            return (0);
        i++;
    }
    u_in->nop = ft_atoi(argv[1]);
    u_in->ttd = ft_atoi(argv[2]);
    u_in->tte = ft_atoi(argv[3]);
    u_in->tts = ft_atoi(argv[4]);
    if (argc == 6)
        u_in->notme = ft_atoi(argv[5]);    
    else
        u_in->notme = -1;
    return (1);
}

int main(int argc, char *argv[])
{
    int             *forks;
    t_in            u_in;
    pthread_mutex_t *pth_mutex;


    forks = (int *)malloc(NUM_PHILO * sizeof(int));
    pth_mutex = (pthread_mutex_t *)malloc(NUM_PHILO * sizeof(pthread_mutex_t));
    if(!check_args(argc, argv, &u_in))
        return (0);
    if (!ft_init_forks(NUM_PHILO, forks))
        return (0);
    if(!ft_init_mutexes(NUM_PHILO, pth_mutex))
        return (0);
    if (!ft_init_philos(NUM_PHILO, pth_mutex, &u_in, forks))
        return (0);

    printf("PHILOS AND MUTEXES CREATED SUCCESSFULLY\n");
    return (0);
}