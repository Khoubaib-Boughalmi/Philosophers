/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:30:12 by kboughal          #+#    #+#             */
/*   Updated: 2023/01/29 17:46:59 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher(t_philosopher *philo)
{
	// if (philo->u_in->nop == 1)
	// {
	// 	my_print("has taken a fork", philo);
	// 	ft_philo_pause(philo, 'd');
	// 	my_print("is dead", philo);
	// 	exit(0);
	// }
	while (1)
	{	
		// pthread_mutex_lock(&(philo->u_in->forks[philo->right]));
		// my_print("has taken a fork", philo);
		// pthread_mutex_lock(&(philo->u_in->forks[philo->left]));
		// my_print("has taken a fork", philo);
		// my_print("is eating", philo);
		// ft_philo_pause(philo, 'e');
		// pthread_mutex_lock(&(philo->u_in->c_lock));
		// philo->last_meal = ft_get_time();
		// philo->pmeals += 1;
		// pthread_mutex_unlock(&(philo->u_in->c_lock));
		// // usleep(1000 * philo->u_in->tte);
		// pthread_mutex_unlock(&(philo->u_in->forks[philo->right]));
		// pthread_mutex_unlock(&(philo->u_in->forks[philo->left]));
		// my_print("is sleeping", philo);
		// ft_philo_pause(philo, 's');
		// // usleep(1000 * philo->u_in->tts);
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
		(*philo)[i].pmeals = 0;
		(*philo)[i].u_in = u_in;
		(*philo)[i].last_meal = ft_get_time();
		(*philo)[i].lock = 1;
		i++;
	}
	return (1);
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

int ft_monitor(t_in *u_in, t_philosopher *philos)
{
	int		i;
	long	timer;
	int		total;

	total = 0;
	while (1)
	{
		i = 0;
		usleep(10);
		while (i < u_in->nop)
		{
			pthread_mutex_lock(&(philos[i].u_in->c_lock));
			timer = ft_get_time() - philos[i].last_meal;
			pthread_mutex_unlock(&(philos[i].u_in->c_lock));
			if (timer >= u_in->ttd)
			{
				my_print("died", &philos[i]);
				return(0);
			}
			if (philos[i].pmeals == u_in->tmeals && philos[i].lock && u_in->tmeals != -1)
			{
				total++;
				philos[i].lock = 0;
				if (total == u_in->nop)
					return (0);
			}
			i++;
		}
	}
}

int	main(int argc, char *argv[])
{
	int				i;
	t_in			*u_in;
	t_philosopher	*philos;
	sem_t			*forks;
	long			timer;
	int				total;

	total = 0;
	if (!parse_args(argc, argv, &u_in))
		return (0);
	if(!ft_init(u_in, forks, &philos))
		return (0);
	create_philos(u_in, philos);
	// if(!ft_monitor(u_in, philos))
	// {
	// 	i = -1;
	// 	while (i++ < u_in->nop)
	// 	{	
	// 		if(pthread_detach(philos[i].philo_thr))
	// 			return (1);
	// 		if(pthread_mutex_destroy(&forks[i]))
	// 			return (1);
	// 		free(forks);
	// 		free(philos);
	// 		free(u_in);
	// 	}
	// }
	return (0);
}
