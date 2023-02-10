/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:06:07 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/10 14:23:05 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = ((t_philosopher *)arg);
	while (1)
	{
		my_print("is thinking", philo);
		pthread_mutex_lock(&(philo->u_in->forks[philo->right]));
		my_print("has taken a fork", philo);
		pthread_mutex_lock(&(philo->u_in->forks[philo->left]));
		my_print("has taken a fork", philo);
		my_print("is eating", philo);
		pthread_mutex_lock(&(philo->u_in->c_lock));
		philo->last_meal = ft_get_time();
		pthread_mutex_unlock(&(philo->u_in->c_lock));
		ft_philo_pause(philo, 'e');
		pthread_mutex_lock(&(philo->u_in->m_lock));
		philo->pmeals += 1;
		pthread_mutex_unlock(&(philo->u_in->m_lock));
		pthread_mutex_unlock(&(philo->u_in->forks[philo->right]));
		pthread_mutex_unlock(&(philo->u_in->forks[philo->left]));
		my_print("is sleeping", philo);
		ft_philo_pause(philo, 's');
	}
}
