/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:52:49 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/12 20:08:27 by gwinnink         ###   ########.fr       */
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
	while (check_flag(philo->has_died))
	{
		if (!check_hunger(philo, tt_die))
		{
			DEBUG(philo->id, "\033[0mpre die");
			if (!die(philo))
			{
				DEBUG(philo->id, "\033[0mdead");
				return (NULL);
			}
			DEBUG(philo->id, "\033[0mpost die");
			return (NULL);
		}
		usleep(200);
	}
	return (NULL);
}
