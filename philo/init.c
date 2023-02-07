/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:26:15 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/07 19:25:05 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	ft_init_forks(t_in *u_in, pthread_mutex_t **forks)
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


int ft_init_mutexes(t_in *u_in)
{
    if (pthread_mutex_init(&(u_in)->c_lock, NULL))
        return (0);
    if (pthread_mutex_init(&(u_in)->p_lock, NULL))
        return (0);
	if (pthread_mutex_init(&(u_in)->m_lock, NULL))
        return (0);
    return (1);
}
int ft_init(t_in *u_in, pthread_mutex_t **forks, t_philosopher **philos)
{
    if (!ft_init_forks(u_in, forks))
		return (0);
	if (!ft_init_philos(u_in, philos))
		return (0);
	if (!ft_init_mutexes(u_in))
		return (0);
    return (1);
}