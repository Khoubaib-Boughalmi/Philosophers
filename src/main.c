/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:30:12 by kboughal          #+#    #+#             */
/*   Updated: 2023/01/27 21:56:51 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosphers.h"

void	*philosopher(void *arg)
{
	t_philosopher	*philo;

	philo = ((t_philosopher *)arg);
	if (philo->u_in->nop == 1)
	{
		my_print("has taken a fork", philo);
		ft_philo_pause(philo, 'd');
		my_print("is dead", philo);
		exit(0);
	}
	while (1)
	{	
		pthread_mutex_lock(&(philo->u_in->forks[philo->right]));
		my_print("has taken a fork", philo);
		pthread_mutex_lock(&(philo->u_in->forks[philo->left]));
		my_print("has taken a fork", philo);
		my_print("is eating", philo);
		pthread_mutex_lock(&(philo->u_in->c_lock));
		philo->last_meal = ft_get_time();
		philo->pmeals += 1;
		pthread_mutex_unlock(&(philo->u_in->c_lock));
		ft_philo_pause(philo, 'e');
		pthread_mutex_unlock(&(philo->u_in->forks[philo->right]));
		pthread_mutex_unlock(&(philo->u_in->forks[philo->left]));
		my_print("is sleeping", philo);
		ft_philo_pause(philo, 's');
		my_print("is thinking", philo);
	}
}

void	my_print(char *str, t_philosopher *philo)
{
	pthread_mutex_lock(&(philo->u_in->p_lock));
	printf("%ld %d %s\n", ft_get_time() - philo->birth, philo->id, str);
	pthread_mutex_unlock(&(philo->u_in->p_lock));
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
		(*philo)[i].id = i;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % u_in->nop;
		(*philo)[i].pmeals = 0;
		(*philo)[i].u_in = u_in;
		(*philo)[i].last_meal = -1;
		(*philo)[i].lock = 1;
		i++;
	}
	return (1);
}

int	create_philos(t_in *u_in, t_philosopher *philo)
{
	int				res;

	create_philos_even(u_in, philo);
	usleep(50);
	create_philos_odd(u_in, philo);
	

	return (1);
}

int	create_philos_even(t_in *u_in, t_philosopher *philo)
{
	int	i;
	int	res;

	i = 0;
	while (i < u_in->nop)
	{
		if (i % 2 == 0)
		{
			philo[i].birth = ft_get_time();
			if (pthread_create(&philo[i].philo_thr, NULL, \
				philosopher, philo + i) != 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int	create_philos_odd(t_in *u_in, t_philosopher *philo)
{
	int	i;
	int	res;

	i = 0;
	while (i < u_in->nop)
	{
		if (i % 2 != 0)
		{
			philo[i].birth = ft_get_time();
			if (pthread_create(&philo[i].philo_thr, NULL, \
				philosopher, philo + i) != 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_forks(t_in *u_in, pthread_mutex_t **forks)
{
	int	i;

	i = -1;
	*forks = (pthread_mutex_t *)malloc(u_in->nop * sizeof(pthread_mutex_t));
	if (!forks)
		return (0);
	while (++i < u_in->nop)
		if (pthread_mutex_init(&(*forks)[i], NULL))
			return (0);
	u_in->forks = *forks;
	return (1);
}

int	check_args(int argc, char *argv[], t_in **u_in)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 2;
	*u_in = (t_in *)malloc(sizeof(t_in));
	if (ft_atoi(argv[1]) <= 0)
		return (0);
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	(*u_in)->nop = ft_atoi(argv[1]);
	(*u_in)->ttd = ft_atoi(argv[2]);
	(*u_in)->tte = ft_atoi(argv[3]);
	(*u_in)->tts = ft_atoi(argv[4]);
	if (argc == 6)
		(*u_in)->tmeals = ft_atoi(argv[5]);
	else
		(*u_in)->tmeals = -1;
	pthread_mutex_init(&(*u_in)->c_lock, NULL);
	pthread_mutex_init(&(*u_in)->p_lock, NULL);
	return (1);
}

long	ft_get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int ft_monitor(t_in *u_in, t_philosopher *philos)
{
	int		i;
	long	timer;
	int		total;

	total = 0;
	while (1)
	{
		i = 0;
		while (i < u_in->nop)
		{
			pthread_mutex_lock(&(philos[i].u_in->c_lock));
			timer = ft_get_time() - philos[i].last_meal;
			pthread_mutex_unlock(&(philos[i].u_in->c_lock));
			if (timer >= u_in->ttd && philos[i].last_meal != -1)
			{
				my_print("is dead", &philos[i]);
				return(0);
			}
			if (philos[i].pmeals == u_in->tmeals && philos[i].lock && u_in->tmeals != -1)
			{
				total++;
				philos[i].lock = 0;
				if (total == u_in->nop)
					return (0);
			}
			usleep(10);
			i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	int				i;
	t_in			*u_in;
	t_philosopher	*philos;
	pthread_mutex_t	*forks;
	long			timer;
	int				total;

	total = 0;
	if (!check_args(argc, argv, &u_in))
		return (0);
	if (!ft_forks(u_in, &forks))
		return (0);
	if (!ft_init_philos(u_in, &philos))
		return (0);
	create_philos(u_in, philos);
	if(!ft_monitor(u_in, philos))
	{
		i = -1;
		while (i++ < u_in->nop)
		{	
			if(pthread_detach(philos[i].philo_thr))
				return (1);
			if(pthread_mutex_destroy(&forks[i]))
				return (1);
			free(forks);
			free(philos);
			free(u_in);
		}
	}
	return (0);
}
