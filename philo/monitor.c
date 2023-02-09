/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:26:16 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/08 19:48:06 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_monitor(t_in *u_in, t_philosopher *philos)
{
	int		i;
	int		total;

	total = 0;
	while (1)
	{
		i = -1;
		usleep(600);
		while (++i < u_in->nop)
		{
			if (ft_get_timer_diff(&philos[i]) >= u_in->ttd)
			{
				my_print("died", &philos[i]);
				return (0);
			}
			if (philos[i].pmeals == u_in->tmeals && philos[i].lock && \
					u_in->tmeals != -1)
			{
				total++;
				philos[i].lock = 0;
				if (total == u_in->nop)
					return (0);
			}
		}
	}
}
