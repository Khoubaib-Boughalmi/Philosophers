/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:26:15 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/03 20:20:24 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_sems(t_in *u_in, sem_t *forks, sem_t *death)
{
	sem_close(forks);
	sem_unlink("/forks");
	sem_close(death);
	sem_unlink("/death");
	forks = sem_open("/forks", O_CREAT, 0644, u_in->nop);
    if (forks == SEM_FAILED) {
        return (0);
    }
	death = sem_open("/death", O_CREAT, 0644, u_in->nop);
    if (death == SEM_FAILED) {
        return (0);
    }
	u_in->forks = forks;
	u_in->death = death;
	return (1);
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
		(*philo)[i].pmeals = 0;
		(*philo)[i].u_in = u_in;
		(*philo)[i].last_meal = ft_get_time();
		(*philo)[i].lock = 1;
		i++;
	}
	return (1);
}

int ft_init(t_philosopher **philos, t_in *u_in, sem_t *forks, sem_t *death)
{
    if (!ft_init_sems(u_in, forks, death))
		return (0);
	if (!ft_init_philos(u_in, philos))
		return (0);
    return (1);
}