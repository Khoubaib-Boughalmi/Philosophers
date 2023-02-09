/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:24:49 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/08 19:31:12 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (!n)
		return ;
	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

long int	ft_atoi_core(char *ptr, unsigned long *i, int sign)
{
	long int		res;

	res = 0;
	while (ptr[*i] != '\0')
	{
		if ((ptr[*i] >= '0' && ptr[*i] <= '9'))
		{
			res = res * 10;
			res += ptr[*i] - '0';
			if (res * sign > 21474483647)
				return (-1);
			if (res * sign < -2147483648)
				return (-1);
			(*i)++;
		}
		else
			return (-1);
	}
	return (res * sign);
}

int	ft_atoi(char *ptr)
{
	unsigned long	i;
	long int		res;
	short			sign;

	sign = 1;
	res = 0;
	i = 0;
	if (ptr[0] == '-')
	{
		sign = -1;
		i++;
	}
	res = ft_atoi_core(ptr, &i, sign);
	return (res);
}

void	my_print(char *str, t_philosopher *philo)
{
	sem_wait(philo->u_in->sem_collection.print);
	printf("%ld %d %s\n", ft_get_time() - philo->birth, philo->id, str);
	sem_post(philo->u_in->sem_collection.print);
}

void	clean_semaphores(t_sem_define *sem_collection)
{
	sem_close(sem_collection->forks);
	sem_unlink("/forks");
	sem_close(sem_collection->death);
	sem_unlink("/death");
	sem_close(sem_collection->food);
	sem_unlink("/food");
	sem_close(sem_collection->print);
	sem_unlink("/print");
}
