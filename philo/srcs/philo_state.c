/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:18:15 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/12 20:28:52 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "printing_utils.h"
#include "time_utils.h"
#include "flag_utils.h"
#include <pthread.h>
#include <stdbool.h>

bool	grab_fork(t_philo *philo, t_flag *fork)
{
	DEBUG(philo->id, "fork mutex\033[0;94m trylock");
	if (pthread_mutex_lock(&fork->mtx) != 0)
		return (false);
	DEBUG(philo->id, "fork mutex\033[0;91m lock");
	// DEBUG(philo->id, "printing mutex\033[0;94m trylock");
	if (pthread_mutex_lock(&philo->printing->mtx) != 0)
		return (false);
	// DEBUG(philo->id, "printing mutex\033[0;91m lock");
	if (!printing(philo, 0, "has taken a fork"))
	{
		if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
			return (false);
		// DEBUG(philo->id, "printing mutex \033[0;92munlock (no print)");
		if (pthread_mutex_unlock(&fork->mtx) != 0)
			return (false);
		DEBUG(philo->id, "fork mutex\033[0;92m unlock");
		return (false);
	}
	if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
		return (false);
	// DEBUG(philo->id, "printing mutex\033[0;92m unlock");
	return (true);
}

bool	eat(t_philo *philo)
{
	// DEBUG(philo->id, "printing mutex\033[0;94m trylock");
	if (pthread_mutex_lock(&philo->printing->mtx) != 0)
		return (false);
	// DEBUG(philo->id, "printing mutex\033[0;91m lock");
	if (pthread_mutex_lock(&philo->lm_flag.mtx) != 0)
		return (false);
	if (!printing(philo, 1, "is eating"))
	{
		if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
			return (false);
		// DEBUG(philo->id, "printing mutex\033[0;92m unlock (no print)");
		return (false);
	}
	if (pthread_mutex_unlock(&philo->lm_flag.mtx) != 0)
		return (false);
	if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
		return (false);
	// DEBUG(philo->id, "printing mutex\033[0;92m unlock");
	better_usleep(philo->tt_eat * 1000);
	return (true);
}

bool	philo_sleep(t_philo *philo)
{
	// DEBUG(philo->id, "printing mutex\033[0;94m trylock");
	if (pthread_mutex_lock(&philo->printing->mtx) != 0)
		return (false);
	// DEBUG(philo->id, "printing mutex\033[0;91m lock");
	if (!printing(philo, 0, "is sleeping"))
	{
		if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
			return (false);
		// DEBUG(philo->id, "printing mutex\033[0;92m unlock (no print)");
		return (false);
	}
	if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
		return (false);
	// DEBUG(philo->id, "printing mutex\033[0;92m unlock");
	better_usleep(philo->tt_sleep * 1000);
	return (true);
}

bool	think(t_philo *philo)
{
	// DEBUG(philo->id, "printing mutex\033[0;94m trylock");
	if (pthread_mutex_lock(&philo->printing->mtx) != 0)
		return (false);
	// DEBUG(philo->id, "printing mutex\033[0;91m lock");
	if (!printing(philo, 0, "is thinking"))
	{
		if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
			return (false);
		// DEBUG(philo->id, "printing mutex\033[0;92m unlock (no print)");
		return (false);
	}
	if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
		return (false);
	// DEBUG(philo->id, "printing mutex\033[0;92m unlock");
	return (true);
}

bool	die(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->has_died->mtx) != 0)
		return (false);
	DEBUG(philo->id, "has_died mutex\033[0;91m lock");
	// DEBUG(philo->id, "printing mutex\033[0;94m trylock");
	// if (pthread_mutex_lock(&philo->printing->mtx) != 0)
	// 	return (false);
	// DEBUG(philo->id, "printing mutex\033[0;91m locked");
	if (!philo->has_died->flag)
	{
		printf("\033[0;9%cm %llu %d died%s\n", (philo->id % 7) + 1 + '0', \
			(get_time() - *philo->start_time) / 1000, philo->id, NORMAL);
		philo->has_died->flag = 1;
		if (pthread_mutex_unlock(&philo->fork1->mtx) == 0)
			DEBUG(philo->id, "fork dropped");
		if (pthread_mutex_unlock(&philo->fork2->mtx) == 0)
			DEBUG(philo->id, "fork dropped");
		if (pthread_mutex_unlock(&philo->has_died->mtx) != 0)
			return (false);
		DEBUG(philo->id, "has_died mutex\033[0;92m unlock");
		return (false);
	}
	if (pthread_mutex_unlock(&philo->has_died->mtx) != 0)
		return (false);
	DEBUG(philo->id, "has_died mutex\033[0;92m unlock");
	// if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
	// 	return (false);
	// DEBUG(philo->id, "printing mutex\033[0;92m unlock");
	return (true);
}
