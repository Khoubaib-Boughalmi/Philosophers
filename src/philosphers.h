/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:10:37 by kboughal          #+#    #+#             */
/*   Updated: 2023/01/27 17:47:26 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSPHERS_H
# define PHILOSPHERS_H

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
int		ft_atoi(const char *ptr);
int		create_philos_even(t_in *u_in, t_philosopher *philo);
int		create_philos_odd(t_in *u_in, t_philosopher *philo);
int		create_philos(t_in *u_in, t_philosopher *philo);
long	ft_get_time(void);
void	ft_philo_pause(t_philosopher *philo, char c);
void	my_print(char *str, t_philosopher *philo);

#	endif