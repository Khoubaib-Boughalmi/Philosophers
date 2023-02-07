/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 18:15:42 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/07 19:03:18 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_death(void *arg)
{
	t_philosopher	*philo;

	philo = ((t_philosopher *)arg);
	while (1)
	{
		usleep(10);
		if (ft_get_timer_diff(philo) >= philo->u_in->ttd)
		{
			sem_post(philo->u_in->sem_collection.death);
			return (0);
		}
	}	
}
