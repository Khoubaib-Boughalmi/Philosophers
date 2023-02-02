/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:26:15 by kboughal          #+#    #+#             */
/*   Updated: 2023/01/31 14:36:06 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_forks(t_in *u_in, sem_t *forks)
{
	forks = sem_open("/forks", O_CREAT, 0644, u_in->nop);
    if (forks == SEM_FAILED) {
        return (0);
    }
	return (1);
}

int	ft_init_philos(t_in *u_in, t_philosopher **philo)
{
	int	i;
	int	res;

	i = 0;
	*philo = (t_philosopher *)malloc(u_in->nop * sizeof(t_philosopher));
	if (!*philo)
		return (0);
	while (i < u_in->nop)
	{
		(*philo)[i].pmeals = 0;
		(*philo)[i].u_in = u_in;
		(*philo)[i].last_meal = ft_get_time();
		(*philo)[i].lock = 1;
		i++;
	}
	return (1);
}

int ft_init_mutexes(t_in *u_in)
{
    if (pthread_mutex_init(&(u_in)->c_lock, NULL))
        return (0);
    if (pthread_mutex_init(&(u_in)->p_lock, NULL))
        return (0);
    return (1);
}

int ft_init(t_in *u_in, sem_t *forks, t_philosopher **philos)
{
    if (!ft_init_forks(u_in, forks))
		return (0);
	if (!ft_init_philos(u_in, philos))
		return (0);
	if (!ft_init_mutexes(u_in))
		return (0);
    return (1);
}