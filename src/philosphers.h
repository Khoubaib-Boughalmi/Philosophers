/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal <kboughal@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:10:37 by kboughal          #+#    #+#             */
/*   Updated: 2023/01/14 16:49:41 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_in
{
    int nop;
    int ttd;
    int tte; 
    int tts;
    int notme;
} t_in;

typedef struct s_philosopher
{
    int             id;
    t_in            *u_in;
    pthread_t       philo_thr;
    pthread_mutex_t *pth_mutex;
}   t_philosopher;

void	ft_bzero(void *s, size_t n);
