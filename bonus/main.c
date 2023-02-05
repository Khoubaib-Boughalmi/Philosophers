/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:30:12 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/03 20:20:32 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *monitor(void *arg)
{
	t_philosopher	*philo;

	philo = ((t_philosopher *)arg);
	while (1)
	{
		usleep(300);
		if (ft_get_timer_diff(philo) >= philo->u_in->ttd)
		{
			sem_post(philo->u_in->sem_collection.death);
			return (0);
		}
	}	
}

void	philosopher(t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < philo->u_in->tmeals)
	{
		sem_wait(philo->u_in->sem_collection.food);
		i++;
	}
	sem_wait(philo->u_in->sem_collection.death);
	pthread_create(&philo->monitor, NULL, monitor, philo);	
	while (1)
	{	
		sem_wait(philo->u_in->sem_collection.forks);
		my_print("has taken a fork", philo);
		sem_wait(philo->u_in->sem_collection.forks);
		my_print("has taken a fork", philo);
		my_print("is eating", philo);
		philo->last_meal = ft_get_time();
		ft_philo_pause(philo, 'e');
		if (philo->u_in->tmeals != -1)
			sem_post(philo->u_in->sem_collection.food);
		sem_post(philo->u_in->sem_collection.forks);
		sem_post(philo->u_in->sem_collection.forks);
		philo->pmeals++;
		my_print("is sleeping", philo);
		ft_philo_pause(philo, 's');
		my_print("is thinking", philo);
	}
}
	
void	my_print(char *str, t_philosopher *philo)
{
	sem_wait(philo->u_in->sem_collection.print);
	printf("%ld %d %s\n", ft_get_time() - philo->birth, philo->id, str);
	sem_post(philo->u_in->sem_collection.print);
}

void	ft_philo_pause(t_philosopher *philo, char c)
{
	long	curr;

	curr = ft_get_time();
	if (c == 'e')
		while (ft_get_time() - curr < philo->u_in->tte)
			usleep(100);
	else if (c == 's')
		while (ft_get_time() - curr < philo->u_in->tts)
			usleep(100);
	else
		while (ft_get_time() - curr < philo->u_in->ttd)
			usleep(100);
}

int	create_philos(t_in *u_in, t_philosopher *philo)
{
	int	i;
	pid_t pid;

	i = 0;
	while (i < u_in->nop)
	{
		pid = fork();
		philo[i].birth = ft_get_time();
		if (!pid)
		{
			philosopher(philo + i);
			return (1);
		}
		else
			philo[i].id = pid;
		i++;
	}
	return (1);
}

void *monitor_food_fun(void *args)
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
	clean_semaphores(&common->sem_collection);
	exit(0);
}

int	main(int argc, char *argv[])
{
	int				i;
	t_in			*u_in;
	t_philosopher	*philos;
	pthread_t		monitor_food;

	i = 0;
	if (!parse_args(argc, argv, &u_in))
		return (0);
	clean_semaphores(&u_in->sem_collection);	
	if(!ft_init(&philos, u_in, &u_in->sem_collection))
		return (0);
	create_philos(u_in, philos);
	usleep(1000);
	if (u_in->tmeals != -1)
		pthread_create(&monitor_food, NULL, monitor_food_fun, philos);	
	sem_wait(u_in->sem_collection.death);
	while (i < u_in->nop)
	{
		kill(philos[i].id, SIGKILL);
		printf("%ld %d died\n", ft_get_time() - philos[i].birth, i);
		i++;
	}
	clean_semaphores(&u_in->sem_collection);
	return (0);
}
