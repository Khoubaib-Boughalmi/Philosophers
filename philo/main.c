/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:30:12 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/10 14:11:34 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	create_philos(t_in *u_in, t_philosopher *philo)
{
	create_philos_even(u_in, philo);
	usleep(50);
	create_philos_odd(u_in, philo);
	return (1);
}

int	create_philos_even(t_in *u_in, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < u_in->nop)
	{
		if (i % 2 == 0)
		{
			philo[i].birth = ft_get_time();
			if (pthread_create(&philo[i].philo_thr, NULL, \
				philosopher_routine, philo + i) != 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int	create_philos_odd(t_in *u_in, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < u_in->nop)
	{
		if (i % 2 != 0)
		{
			philo[i].birth = ft_get_time();
			if (pthread_create(&philo[i].philo_thr, NULL, \
				philosopher_routine, philo + i) != 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	int				i;
	t_in			*u_in;
	t_philosopher	*philos;
	pthread_mutex_t	*forks;

	if (!parse_args(argc, argv, &u_in))
		return (0);
	if (!ft_init(u_in, &forks, &philos))
		return (0);
	create_philos(u_in, philos);
	if (!ft_monitor(u_in, philos))
	{
		i = -1;
		while (i++ < u_in->nop)
		{
			if (pthread_detach(philos[i].philo_thr))
				return (1);
			if (pthread_mutex_destroy(&forks[i]))
				return (1);
		}
		free(forks);
		free(philos);
		free(u_in);
	}
	return (0);
}
