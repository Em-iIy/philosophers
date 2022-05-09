/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:52:49 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/09 18:44:43 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "time_utils.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

static bool	check_hunger(uint64_t tt_die, uint64_t *last_meal, uint64_t *start_time)
{
	if (*last_meal)
	{
		if ((get_time() - *last_meal) / 1000 > tt_die)
			return (false);
	}
	else
	{
		if ((get_time() - *start_time) / 1000 > tt_die)
			return (false);
	}
	return (true);
}

void	*philo_monitor(void *vars)
{
	t_philo		philo;
	uint64_t	tt_die;

	philo = *(t_philo *)vars;
	tt_die = philo.tt_die;
	while (*philo.last_meal == 0)
		usleep(100);
	while (check_hunger(tt_die, philo.last_meal, philo.start_time) && philo.has_died->flag == 0)
		usleep(500);
	if (philo.has_died->flag)
		return (NULL);
	pthread_mutex_lock(&(philo.has_died->mtx));
	philo.has_died->flag = 1;
	printing(philo, NULL, "died\n", 1);
	pthread_mutex_unlock(&(philo.has_died->mtx));
	return (NULL);
}
