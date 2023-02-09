/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:10:37 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/08 19:30:21 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_sem_define
{
	sem_t			*forks;
	sem_t			*death;
	sem_t			*food;
	sem_t			*print;
}	t_sem_define;

typedef struct s_in
{
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				tmeals;
	t_sem_define	sem_collection;
	pthread_mutex_t	c_lock;
	pthread_mutex_t	p_lock;
}	t_in;

typedef struct s_philosopher
{
	pid_t			id;
	int				r_id;
	int				pmeals;
	int				lock;
	long			last_meal;
	long			birth;
	t_in			*u_in;
	pthread_t		monitor;

}	t_philosopher;

void	ft_bzero(void *s, size_t n);
int		ft_atoi(char *ptr);
int		create_philos_even(t_in *u_in, t_philosopher *philo);
int		create_philos_odd(t_in *u_in, t_philosopher *philo);
int		create_philos(t_in *u_in, t_philosopher *philo);
long	ft_get_time(void);
void	ft_pause(t_philosopher *philo, char c);
void	my_print(char *str, t_philosopher *philo);
int		parse_args(int argc, char *argv[], t_in **u_in);
int		ft_init_sems(t_in *u_in, t_sem_define *sem_collection);
int		ft_init(t_philosopher **philos, t_in *u_in, \
			t_sem_define *sem_collection);
int		ft_init_philos(t_in *u_in, t_philosopher **philo);
int		ft_get_timer_diff(t_philosopher *philos);
void	clean_semaphores(t_sem_define *sem_collection);
void	*monitor_death(void *arg);
void	philosopher_routine(t_philosopher *philo);
void	*monitor_food_fun(void *args);
#	endif