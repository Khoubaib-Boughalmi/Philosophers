/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:15:42 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/09 18:11:13 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_death(void *arg)
{
	t_philosopher	*philo;

	philo = ((t_philosopher *)arg);
	while (1)
	{
		usleep(500);
		if (ft_get_timer_diff(philo) >= philo->u_in->ttd)
		{
			sem_post(philo->u_in->sem_collection.death);
			return (0);
		}
	}	
}

void	*monitor_food(void *args)
{
	t_philosopher	*philos;
	t_in			*common;
	int				i;

	i = 0;
	philos = ((t_philosopher *)args);
	common = philos[0].u_in;
	while (i < common->tmeals * common->nop)
	{
		sem_wait(common->sem_collection.food);
		i++;
	}
	i = -1;
	while (++i < common->nop)
	{
		kill(philos[i].id, SIGKILL);
	}
	free(common);
	free(philos);
	exit(0);
}
