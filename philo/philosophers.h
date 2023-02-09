/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:10:37 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/08 19:48:52 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_in
{
	int				nop;
	int				ttd;
	int				tte;
	int				tts;
	int				tmeals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	c_lock;
	pthread_mutex_t	p_lock;
	pthread_mutex_t	m_lock;
}	t_in;

typedef struct s_philosopher
{
	int				id;
	int				left;
	int				right;
	int				pmeals;
	int				lock;
	long			last_meal;
	long			birth;
	t_in			*u_in;
	pthread_t		philo_thr;

}	t_philosopher;

void	ft_bzero(void *s, size_t n);
int		ft_atoi(char *ptr);
int		create_philos_even(t_in *u_in, t_philosopher *philo);
int		create_philos_odd(t_in *u_in, t_philosopher *philo);
int		create_philos(t_in *u_in, t_philosopher *philo);
long	ft_get_time(void);
void	ft_philo_pause(t_philosopher *philo, char c);
void	my_print(char *str, t_philosopher *philo);
int		parse_args(int argc, char *argv[], t_in **u_in);
long	ft_get_time(void);
int		ft_init_forks(t_in *u_in, pthread_mutex_t **forks);
int		ft_init(t_in *u_in, pthread_mutex_t **forks, t_philosopher **philos);
int		ft_init_philos(t_in *u_in, t_philosopher **philo);
int		ft_get_timer_diff(t_philosopher *philos);
int		ft_init_mutexes(t_in *u_in);
void	*philosopher_routine(void *arg);
int		ft_monitor(t_in *u_in, t_philosopher *philos);

#	endif