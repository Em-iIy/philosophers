/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:52:49 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/17 15:27:39 by gwinnink         ###   ########.fr       */
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

	if (check_flag(&philo->n_meals))
		return (true);
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
	while (check_flag(philo->has_died) && !check_flag(&philo->n_meals))
	{
		if (!check_hunger(philo, tt_die))
		{
			if (!die(philo))
				return (NULL);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	*single_philo_monitor(void *vars)
{
	t_table		*table;
	uint64_t	tt_die;
	int			i;

	table = (t_table *)vars;
	tt_die = (uint64_t) table->tt_die;
	while (check_flag(&table->has_died) && !check_flag(&table->done_eating))
	{
		i = 0;
		while (i < table->n_philo)
		{
			if (!check_hunger(&table->philos[i], tt_die))
			{
				if (!die(&table->philos[i]))
					return (NULL);
				return (NULL);
			}
			usleep(200);
			i++;
		}
	}
	return (NULL);
}
