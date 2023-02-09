/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:23:39 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/08 19:28:56 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	parse_args(int argc, char *argv[], t_in **u_in)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (0);
	i = 2;
	*u_in = (t_in *)malloc(sizeof(t_in));
	if (ft_atoi(argv[1]) <= 0 || !*u_in)
		return (0);
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (0);
		i++;
	}
	(*u_in)->nop = ft_atoi(argv[1]);
	(*u_in)->ttd = ft_atoi(argv[2]);
	(*u_in)->tte = ft_atoi(argv[3]);
	(*u_in)->tts = ft_atoi(argv[4]);
	if (argc == 6)
		(*u_in)->tmeals = ft_atoi(argv[5]);
	else
		(*u_in)->tmeals = -1;
	return (1);
}
