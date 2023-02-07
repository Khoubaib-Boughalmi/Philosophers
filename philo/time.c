/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:43:46 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/07 19:25:15 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

long	ft_get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_get_timer_diff(t_philosopher *philos)
{
	int	timer;
	pthread_mutex_lock(&(philos->u_in->c_lock));
	timer = ft_get_time() - philos->last_meal;
	pthread_mutex_unlock(&(philos->u_in->c_lock));
	return (timer);
}