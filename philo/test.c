/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:20:54 by kboughal          #+#    #+#             */
/*   Updated: 2023/02/09 17:21:31 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char *argv[])
{
	int				i;
	t_in			*u_in;
	t_philosopher	*philos;
	pthread_mutex_t	*forks;

	if (!parse_args(argc, argv, &u_in))
		return (0);
	if (!ft_init(u_in, &forks, &philos))
		return (0);
	create_philos(u_in, philos);
	if (!ft_monitor(u_in, philos))
	{
		i = -1;
		while (i++ < u_in->nop)
		{
			if (pthread_detach(philos[i].philo_thr))
				return (1);
			if (pthread_mutex_destroy(&forks[i]))
				return (1);
		}
		free(forks);
		free(philos);
		free(u_in);
	}
	return (0);
}
