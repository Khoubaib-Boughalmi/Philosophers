/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:14:28 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/09 17:56:19 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	philosopher_routine_core(t_philosopher *philo)
{
	while (1)
	{	
		sem_wait(philo->u_in->sem_collection.forks);
		my_print("has taken a fork", philo);
		sem_wait(philo->u_in->sem_collection.forks);
		my_print("has taken a fork", philo);
		my_print("is eating", philo);
		ft_pause(philo, 'e');
		philo->last_meal = ft_get_time();
		sem_post(philo->u_in->sem_collection.forks);
		sem_post(philo->u_in->sem_collection.forks);
		my_print("is sleeping", philo);
		if (philo->u_in->tmeals != -1)
			sem_post(philo->u_in->sem_collection.food);
		ft_pause(philo, 's');
		my_print("is thinking", philo);
	}
}

void	philosopher_routine(t_philosopher *philo)
{
	int	i;

	i = -1;
	while (++i < philo->u_in->tmeals)
		sem_wait(philo->u_in->sem_collection.food);
	sem_wait(philo->u_in->sem_collection.death);
	pthread_create(&philo->monitor, NULL, monitor_death, philo);
	philosopher_routine_core(philo);
}
