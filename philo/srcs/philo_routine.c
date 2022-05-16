/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:07:35 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/16 16:19:13 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "time_utils.h"
#include "flag_utils.h"
#include "printing_utils.h"
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

static bool	philo_routine_even(t_philo *philo)
{
	usleep(2000);
	while (check_flag(philo->has_died) && philo->n_meals)
	{
		if (grab_fork(philo, philo->fork1) != true)
			return (false);
		if (grab_fork(philo, philo->fork2) != true)
			return (false);
		if (eat(philo) != true)
			return (false);
		if (philo_sleep(philo) != true)
			return (false);
		if (think(philo) != true)
			return (false);
		philo->n_meals--;
	}
	return (true);
}

static bool	philo_routine_odd(t_philo *philo)
{
	while (check_flag(philo->has_died) && philo->n_meals)
	{
		if (grab_fork(philo, philo->fork2) != true)
			return (false);
		if (grab_fork(philo, philo->fork1) != true)
			return (false);
		if (eat(philo) != true)
			return (false);
		if (philo_sleep(philo) != true)
			return (false);
		if (think(philo) != true)
			return (false);
		philo->n_meals--;
	}
	return (true);
}

void	*philo_routine(void *vars)
{
	t_philo		philo;
	pthread_t	monitor;
	uint64_t	last_meal;
	bool		done_eating;

	philo = *(t_philo *)vars;
	last_meal = 0;
	philo.last_meal = &last_meal;
	while (!check_time_stamp(&philo.printing->mtx, philo.start_time))
		usleep(200);
	if (pthread_create(&monitor, NULL, &philo_monitor, (void *)&philo) != 0)
		return (NULL);
	if (philo.id & 1)
		done_eating = philo_routine_odd(&philo);
	else
		done_eating = philo_routine_even(&philo);
	// if (done_eating)
	// 	pthread_detach(monitor);
	if (pthread_join(monitor, NULL) != 0)
		return (NULL);
	return (NULL);
}
