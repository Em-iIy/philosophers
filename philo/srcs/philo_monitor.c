/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:52:49 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/10 19:22:49 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "time_utils.h"
#include "printing_utils.h"
#include "flag_utils.h"
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

// static uint64_t	check_last_meal(uint64_t *last_meal, t_flag *lm_flag)
// {
// 	uint64_t	ret;

// 	// if (pthread_mutex_lock(&lm_flag->mtx) != 0)
// 	// 	return (0);
// 	ret = *last_meal;
// 	// if (pthread_mutex_unlock(&lm_flag->mtx) != 0)
// 	// 	return (0);
// 	return (ret);
// }

static bool	check_hunger(uint64_t tt_die, uint64_t *last_meal, t_flag *lm_flag, \
								uint64_t *start_time)
{
	if (!*last_meal)
	{
		if ((get_time() - *start_time) / 1000 > tt_die)
			return (false);
	}
	else
	{
		// if (pthread_mutex_lock(&lm_flag->mtx) != 0)
		// 	return (false);
		if ((get_time() - *last_meal) / 1000 > tt_die)
			return (false);
		// if (pthread_mutex_unlock(&lm_flag->mtx) != 0)
		// 	return (0);
	}
	return (true);
	(void) lm_flag;
}

void	*philo_monitor(void *vars)
{
	t_philo		philo;
	uint64_t	tt_die;

	philo = *(t_philo *)vars;
	tt_die = philo.tt_die;
	while (*philo.start_time == 0)
		usleep(100);
	while (check_hunger(tt_die, philo.last_meal, &philo.lm_flag, \
							philo.start_time) && check_flag(philo.has_died))
		usleep(500);
	if (die(philo))
		return (NULL);
	return (NULL);
}
