/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:18:15 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/24 14:23:56 by gwinnink         ###   ########.fr       */
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
	if (pthread_mutex_lock(&fork->mtx) != 0)
		func_error(philo, "mutex lock error\n");
	if (pthread_mutex_lock(&philo->printing->mtx) != 0)
		func_error(philo, "mutex lock error\n");
	if (!printing(philo, 0, "has taken a fork"))
	{
		if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
			func_error(philo, "mutex unlock error\n");
		return (false);
	}
	if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
		func_error(philo, "mutex unlock error\n");
	return (true);
}

bool	eat(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->printing->mtx) != 0)
		func_error(philo, "mutex lock error\n");
	if (pthread_mutex_lock(&philo->lm_flag.mtx) != 0)
		func_error(philo, "mutex lock error\n");
	if (!printing(philo, 1, "is eating"))
	{
		if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
			func_error(philo, "mutex unlock error\n");
		return (false);
	}
	if (pthread_mutex_unlock(&philo->lm_flag.mtx) != 0)
		func_error(philo, "mutex unlock error\n");
	if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
		func_error(philo, "mutex unlock error\n");
	better_usleep(philo->tt_eat * 1000);
	if (pthread_mutex_unlock(&philo->fork1->mtx) != 0)
		func_error(philo, "mutex unlock error\n");
	if (pthread_mutex_unlock(&philo->fork2->mtx) != 0)
		func_error(philo, "mutex unlock error\n");
	return (true);
}

bool	philo_sleep(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->printing->mtx) != 0)
		func_error(philo, "mutex lock error\n");
	if (!printing(philo, 0, "is sleeping"))
	{
		if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
			func_error(philo, "mutex unlock error\n");
		return (false);
	}
	if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
		func_error(philo, "mutex unlock error\n");
	better_usleep(philo->tt_sleep * 1000);
	return (true);
}

bool	think(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->printing->mtx) != 0)
		func_error(philo, "mutex lock error\n");
	if (!printing(philo, 0, "is thinking"))
	{
		if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
			func_error(philo, "mutex unlock error\n");
		return (false);
	}
	if (pthread_mutex_unlock(&philo->printing->mtx) != 0)
		func_error(philo, "mutex unlock error\n");
	return (true);
}

bool	die(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->has_died->mtx) != 0)
		error_msg("%smutex lock error%s\n");
	if (!philo->has_died->flag)
	{
		printf("\033[0;9%cm%llu %d died%s\n", (philo->id % 7) + 1 + '0', \
			(get_time() - *philo->start_time) / 1000, philo->id, NORMAL);
		philo->has_died->flag = 1;
		if (pthread_mutex_unlock(&philo->fork1->mtx) != 0)
			error_msg("%smutex unlock error%s\n");
		if (pthread_mutex_unlock(&philo->fork2->mtx) != 0)
			error_msg("%smutex unlock error%s\n");
	}
	if (pthread_mutex_unlock(&philo->has_died->mtx) != 0)
		error_msg("%smutex unlock error%s\n");
	return (true);
}
