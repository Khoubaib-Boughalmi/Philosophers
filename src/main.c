/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:30:12 by kboughal          #+#    #+#             */
/*   Updated: 2023/01/20 15:20:38 by kboughal         ###   ########.fr       */
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
        printf("%ld %d has taken a fork\n", ft_get_time() - philo->u_in->birth, philo->id);
        pthread_mutex_lock(&(philo->u_in->forks[philo->left]));
        printf("%ld %d has taken a fork\n", ft_get_time() - philo->u_in->birth, philo->id);
        pthread_mutex_lock(&(philo->u_in->lock));
        philo->u_in->last_meal = ft_get_time();
        pthread_mutex_unlock(&(philo->u_in->lock));
        printf("%ld %d is eating\n", ft_get_time() - philo->u_in->birth, philo->id);
        ft_philo_pause(philo, 'e');
        pthread_mutex_unlock(&(philo->u_in->forks[philo->right]));
        pthread_mutex_unlock(&(philo->u_in->forks[philo->left]));
        printf("%ld %d is sleeping\n", ft_get_time() - philo->u_in->birth, philo->id);
        ft_philo_pause(philo, 's');
        printf("%ld %d is thinking\n", ft_get_time() - philo->u_in->birth, philo->id);
    }
}

void ft_philo_pause(t_philosopher *philo, char c)
{
    long curr;

    curr = ft_get_time();

    if (c == 'e')
        while (ft_get_time() - curr < philo->u_in->tte)
            usleep(1);
    else
        while (ft_get_time() - curr < philo->u_in->tts)
            usleep(1);
}

int ft_init_philos(t_in *u_in, t_philosopher **philo)
{
    int             i;
    int             res;

    i = 0;
    *philo = (t_philosopher *)malloc(u_in->nop * sizeof(t_philosopher));
    if(!*philo)
        return (0);
    while (i < u_in->nop)
    {
        (*philo)[i].id = i;
        (*philo)[i].left= i;
        (*philo)[i].right = (i + 1) % u_in->nop;
        (*philo)[i].u_in= u_in;
        i++;
    }
    create_philos(u_in, *philo);
    return (1);
}

int create_philos(t_in *u_in, t_philosopher *philo)
{
    int res;
    
    // create_philos_odd(u_in, philo);
    // usleep(100);
    create_philos_even(u_in, philo);
    int i = 0;
    while (i < u_in->nop)
    {
        // pthread_join(philo[i].philo_thr, NULL);
        pthread_detach(philo[i].philo_thr);
        if(res)
            return (0);
        i++;
    }
    return (1);
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
            philo[i].u_in->birth = ft_get_time();
            if (pthread_create(&philo[i].philo_thr, NULL, philosopher, philo + i) != 0)
			    return (0);
            // pthread_join(philo[i].philo_thr, NULL);
		    // if (pthread_detach(philo[i].philo_thr) != 0)
			//     return (0);
            // pthread_join(philo[i].philo_thr, NULL);
            // pthread_detach(philo[i].philo_thr);
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
            philo[i].u_in->birth = ft_get_time();
            if (pthread_create(&philo[i].philo_thr, NULL, philosopher, philo + i) != 0)
			    return (0);
            // pthread_join(philo[i].philo_thr, NULL);
		    // if (pthread_detach(philo[i].philo_thr) != 0)
			//     return (0);
            // pthread_join(philo[i].philo_thr, NULL);
            // pthread_detach(philo[i].philo_thr);
        }        
        i++;
    }
    return (1);
}

int ft_forks(t_in *u_in, pthread_mutex_t **forks)
{
    int i;

    i = -1;
    *forks = (pthread_mutex_t *)malloc(u_in->nop * sizeof(pthread_mutex_t));
    if(!forks)
        return (0);
    while (++i < u_in->nop)
        if(pthread_mutex_init(&(*forks)[i], NULL))
            return (0);
    u_in->forks = *forks;
    return (1);
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

int ft_nights_watch(t_in *u_in, t_philosopher *philo)
{
    int i;

    i = 0;
    while (1)
    {
        while (i < u_in->nop)
        {
            printf("THE WATCHER");
            if (u_in->ttd > ft_get_time() - philo[i].u_in->last_meal)
            {
                printf("%ld %d died\n", ft_get_time() - philo[i].u_in->birth, philo->id);
                return 0;
            }
            i++;
            usleep(50);
        }
        i = 0;
    }
}

long	ft_get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int main(int argc, char *argv[])
{
    t_in            *u_in;
    t_philosopher   *philos;
    pthread_mutex_t *forks;

    if(!check_args(argc, argv, &u_in))
        return (0);
    if (!ft_forks(u_in, &forks))
        return (0);
    if(!ft_init_philos(u_in, &philos))
        return (0);
    // if (!ft_nights_watch(u_in, philos))
    // {
    //     exit(EXIT_SUCCESS);
    // }

    // int i;
    // i = 0;
    // while (1)
    // {
    //     printf("THE WATCHER");
    //     while (i < u_in->nop)
    //     {
    //         if (u_in->ttd > ft_get_time() - philos[i].u_in->last_meal)
    //         {
    //             printf("%ld %d died\n", ft_get_time() - philos[i].u_in->birth, philos->id);
    //             return 0;
    //         }
    //         i++;            
    //     }
    //     i = 0;
    // }
    return (0);
}