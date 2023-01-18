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

void    *philosopher(void *arg)
{
    t_philosopher *philo;

    philo = ((t_philosopher *)arg);
    while (1)
    {    
        pthread_mutex_lock(&(philo->u_in->forks[philo->right]));
        printf("philo %d has taken a fork\n", philo->id);
        pthread_mutex_lock(&(philo->u_in->forks[philo->left]));
        printf("philo %d has taken a fork\n", philo->id);
        printf("philo %d is eating\n", philo->id);
        printf("philo %d is sleeping\n", philo->id);
        printf("philo %d is thinking\n", philo->id);
        pthread_mutex_unlock(&(philo->u_in->forks[philo->right]));
        pthread_mutex_unlock(&(philo->u_in->forks[philo->left]));
    }
    return (NULL);
}

int ft_init_philos(t_in *u_in, t_philosopher *philo)
{
    int             i;
    int             res;

    i = 0;
    philo = (t_philosopher *)malloc(u_in->nop * sizeof(t_philosopher));
    if(!philo)
        return (0);
    while (i < u_in->nop)
    {
        philo[i].id = i;
        philo[i].left= i;
        philo[i].right = (i + 1) % u_in->nop;
        philo[i].u_in= u_in;
        i++;
    }
    create_philos(u_in, philo);
    return (1);
}

int create_philos(t_in *u_in, t_philosopher *philo)
{
    create_philos_even(u_in, philo);
    usleep(100);
    create_philos_odd(u_in, philo);
}

int create_philos_even(t_in *u_in, t_philosopher *philo)
{
    int i;
    int res;

    i = 0;
    while (i < u_in->nop)
    {
        if (i % 2 == 0)
        {
            res = pthread_create(&(philo[i].philo_thr), NULL, philosopher, &philo[i]);
            if(res)
                return (0);
            res = pthread_join(philo[i].philo_thr, NULL);  
            if(res)
                return (0);
        }
        i++;     
    }
    return (1);
}

int create_philos_odd(t_in *u_in, t_philosopher *philo)
{
    int i;
    int res;

    i = 0;
    while (i < u_in->nop)
    {
        if (i % 2 != 0)
        {
            res = pthread_create(&(philo[i].philo_thr), NULL, philosopher, &philo[i]);
            if(res)
                return (0);
            res = pthread_join(philo[i].philo_thr, NULL);  
            if(res)
                return (0);
        }        
        i++;
    }
    return (1);
}

pthread_mutex_t *ft_forks(t_in *u_in, pthread_mutex_t *forks)
{
    int i;

    i = -1;
    forks = (pthread_mutex_t *)malloc(u_in->nop * sizeof(pthread_mutex_t));
    if(!forks)
        return (0);
    while (++i < u_in->nop)
        pthread_mutex_init(&forks[i], NULL);
    u_in->forks = forks;
    return (forks);
}

int check_args(int argc, char *argv[], t_in **u_in)
{
    int i;

    if (argc < 5 || argc > 6 )
        return (0);
    i = 2;
    *u_in = (t_in *)malloc(sizeof(t_in));
    if(ft_atoi(argv[1]) <= 0)
            return (0);
    while (i < argc)
    {
        if(ft_atoi(argv[i]) < 0)
            return (0);
        i++;
    }
    (*u_in)->nop = ft_atoi(argv[1]);
    (*u_in)->ttd = ft_atoi(argv[2]);
    (*u_in)->tte = ft_atoi(argv[3]);
    (*u_in)->tts = ft_atoi(argv[4]);
    if (argc == 6)
        (*u_in)->tmeals = ft_atoi(argv[5]);    
    else
        (*u_in)->tmeals = -1;
    return (1);
}

int main(int argc, char *argv[])
{
    t_in            *u_in;
    t_philosopher   *philos;
    pthread_mutex_t *forks;

    if(!check_args(argc, argv, &u_in))
        return (0);
    forks = ft_forks(u_in, forks);
    if (!forks)
        return (0);
    if(!ft_init_philos(u_in, philos))
        return (0);
    // printf("PHILOS AND MUTEXES CREATED SUCCESSFULLY\n", u_in->nop);
    return (0);
}