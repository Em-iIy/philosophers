/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:52:49 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/11 17:41:01 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "time_utils.h"
#include "printing_utils.h"
#include "flag_utils.h"
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

static bool	check_hunger(t_philo *philo, uint64_t tt_die)
{
	uint64_t	lm;

	lm = check_time_stamp(&philo->lm_flag.mtx, philo->last_meal);
	if (!lm)
	{
		if ((get_time() - *philo->start_time) / 1000 > tt_die)
			return (false);
	}
	else
	{
		if ((get_time() - lm) / 1000 > tt_die)
			return (false);
	}
	return (true);
}

void	*philo_monitor(void *vars)
{
	t_philo		*philo;
	uint64_t	tt_die;

	philo = (t_philo *)vars;
	tt_die = (uint64_t) philo->tt_die;
	while (!check_time_stamp(&philo->printing->mtx, philo->start_time))
		usleep(200);
	while (check_hunger(philo, tt_die) && check_flag(philo->has_died))
		usleep(200);
	if (die(philo))
		return (NULL);
	return (NULL);
}
