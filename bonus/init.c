/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:26:15 by kboughal          #+#    #+#             */
/*   Updated: 2023/01/29 17:35:01 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_forks(t_in *u_in, sem_t *forks)
{
	forks = sem_open("/forks", O_CREAT, 0644, u_in->nop);
    if (forks == SEM_FAILED) {
        return (0);
    }
	return (1);
}

int ft_init(t_in *u_in, sem_t *forks, t_philosopher **philos)
{
    if (!ft_init_forks(u_in, forks))
		return (0);
	if (!ft_init_philos(u_in, philos))
		return (0);
    pthread_mutex_init(&(u_in)->c_lock, NULL);
	pthread_mutex_init(&(u_in)->p_lock, NULL);
    return (1);
}