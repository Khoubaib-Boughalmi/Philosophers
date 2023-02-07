/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:30:12 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/07 19:49:28 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_philos(t_in *u_in, t_philosopher *philo)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < u_in->nop)
	{
		pid = fork();
		philo[i].birth = ft_get_time();
		if (!pid)
		{
			philosopher_routine(philo + i);
			return (1);
		}
		else
			philo[i].id = pid;
		i++;
	}
	return (1);
}

void	*monitor_food_fun(void *args)
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
		kill(philos[i].id, SIGKILL);
	exit(0);
}

void ft_terminate(t_in *u_in, t_philosopher *philos)
{
	int	i;

	i = 0;
	sem_wait(u_in->sem_collection.death);
	while (i < u_in->nop)
	{
		kill(philos[i].id, SIGKILL);
		printf("%ld %d died\n", ft_get_time() - philos[i].birth, i);
		i++;
	}
	if (u_in->tmeals != -1)
		sem_post(u_in->sem_collection.food);
	clean_semaphores(&u_in->sem_collection);
}

int	main(int argc, char *argv[])
{
	t_in			*u_in;
	t_philosopher	*philos;
	pthread_t		monitor_food;

	if (!parse_args(argc, argv, &u_in))
		return (0);
	clean_semaphores(&u_in->sem_collection);
	if (!ft_init(&philos, u_in, &u_in->sem_collection))
		return (0);
	create_philos(u_in, philos);
	usleep(1000);
	if (u_in->tmeals != -1)
		pthread_create(&monitor_food, NULL, monitor_food_fun, philos);
	ft_terminate(u_in, philos);
	return (0);
}
