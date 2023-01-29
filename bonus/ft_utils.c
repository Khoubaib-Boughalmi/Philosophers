/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:24:49 by kboughal          #+#    #+#             */
/*   Updated: 2023/01/28 17:26:47 by kboughal         ###   ########.fr       */
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

int	ft_atoi(const char *ptr)
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
	while ((ptr[i] >= '0' && ptr[i] <= '9') && ptr[i] != '\0')
	{
		res = res * 10;
		res += ptr[i] - '0';
		if (res * sign > 21474483647)
			return (0);
		if (res * sign < -2147483648)
			return (0);
		i++;
	}
	return (res * sign);
}

long	ft_get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}