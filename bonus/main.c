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

void	philosopher(t_philosopher *philo)
{
	sem_wait(philo->u_in->death);	
	while (1)
	{	
		sem_wait(philo->u_in->forks);
		my_print("has taken a fork", philo);
		sem_wait(philo->u_in->forks);
		my_print("has taken a fork", philo);
		my_print("is eating", philo);
		philo->last_meal = ft_get_time();
		ft_philo_pause(philo, 'e');
		sem_post(philo->u_in->forks);
		sem_post(philo->u_in->forks);
		my_print("is sleeping", philo);
		ft_philo_pause(philo, 's');
		my_print("is thinking", philo);
	}
}
	
void	my_print(char *str, t_philosopher *philo)
{
	printf("%ld %d %s\n", ft_get_time() - philo->birth, philo->id, str);
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
		{
			philo[i].id = pid;
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
	sem_t			*forks;
	sem_t			*death;
	long			timer;
	int				total;

	total = 0;
	if (!parse_args(argc, argv, &u_in))
		return (0);
	if(!ft_init(&philos, u_in, forks, death))
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
	usleep(800);
	sem_wait(u_in->death);
	printf("HELLO FROM MAIIIIIIIIIIIIIIIIN\n");
	// sem_close(forks);
	// sem_unlink("/forks");
	// sem_close(death);
	// sem_unlink("/death");
	return (0);
}
