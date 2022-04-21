/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:52:49 by gwinnink          #+#    #+#             */
/*   Updated: 2022/04/21 15:30:01 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "time_utils.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*philo_monitor(void *vars)
{
	t_philo			philo;
	unsigned long	tt_die;

	philo = *(t_philo *)vars;
	tt_die = philo.tt_die;
	while (*philo.last_meal == 0)
		usleep(100);
	while ((get_time() - *philo.last_meal) / 1000 <= tt_die && philo.has_died->flag == 0)
		usleep(50);
	if (philo.has_died->flag)
		return (NULL);
	pthread_mutex_lock(&(philo.has_died->mtx));
	philo.has_died->flag = 1;
	printing(philo, NULL, "died\n", 1);
	pthread_mutex_unlock(&(philo.has_died->mtx));
	return (NULL);
}
