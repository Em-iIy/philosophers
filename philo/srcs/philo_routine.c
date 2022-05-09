/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:07:35 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/09 18:44:17 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"
#include "time_utils.h"
#include <unistd.h>

static int	philo_routine_even(t_philo *philo)
{
	usleep(250);
	while (!philo->has_died->flag)
	{
		pthread_mutex_lock(&(philo->fork1->mtx));
		printing(*philo, NULL, "has taken a fork\n", 0); // error prone
		pthread_mutex_lock(&(philo->fork2->mtx));
		printing(*philo, NULL, "has taken a fork\n", 0); // error prone
		printing(*philo, philo->last_meal, "is eating\n", 0); // error prone
		better_usleep(philo->tt_eat * 1000);
		pthread_mutex_unlock(&(philo->fork1->mtx));
		pthread_mutex_unlock(&(philo->fork2->mtx));
		printing(*philo, NULL, "is sleeping\n", 0); // error prone
		better_usleep(philo->tt_sleep * 1000);
		printing(*philo, NULL, "is thinking\n", 0); // error prone
	}
	return (0);
}

static int	philo_routine_odd(t_philo *philo)
{
	while (!philo->has_died->flag)
	{
		pthread_mutex_lock(&(philo->fork2->mtx));
		printing(*philo, NULL, "has taken a fork\n", 0); // error prone
		pthread_mutex_lock(&(philo->fork1->mtx));
		printing(*philo, NULL, "has taken a fork\n", 0); // error prone
		printing(*philo, philo->last_meal, "is eating\n", 0); // error prone
		better_usleep(philo->tt_eat * 1000);
		pthread_mutex_unlock(&(philo->fork2->mtx));
		pthread_mutex_unlock(&(philo->fork1->mtx));
		printing(*philo, NULL, "is sleeping\n", 0); // error prone
		better_usleep(philo->tt_sleep * 1000);
		printing(*philo, NULL, "is thinking\n", 0); // error prone
	}
	return (0);
}

void	*philo_routine(void *vars)
{
	t_philo		philo;
	pthread_t	monitor;
	uint64_t	last_meal;

	philo = *(t_philo *)vars;
	last_meal = 0;
	philo.last_meal = &last_meal;
	if (pthread_create(&monitor, NULL, &philo_monitor, (void *)&philo) != 0)
		return (NULL);
	while (*philo.start_time == 0)
		usleep(100);
	if (philo.id & 1)
		philo_routine_odd(&philo);
	else
		philo_routine_even(&philo);
	pthread_join(monitor, NULL);
	return (NULL);
}
