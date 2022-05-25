/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:43:38 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/25 10:23:24 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "not_libft.h"
#include "flag_utils.h"
#include <stdlib.h>
#include <stdbool.h>

static bool	fill_philo(t_philo *philo, t_input input, t_table *table)
{
	philo->tt_die = input.tt_die;
	philo->tt_eat = input.tt_eat;
	philo->tt_sleep = input.tt_sleep;
	philo->has_died = &(table->has_died);
	philo->printing = &(table->printing);
	philo->done_eating = &(table->done_eating);
	philo->start_time = &(table->start_time);
	philo->last_meal = 0;
	philo->lm_flag = create_flag();
	philo->n_meals = create_flag();
	if (philo->lm_flag.flag == 1 || philo->n_meals.flag == 1)
		return (false);
	philo->n_meals.flag = input.n_meals;
	return (true);
}

t_philo	*init_philos(int n, t_table *table, t_input input)
{
	t_philo	*ret;
	int		i;

	i = 0;
	ret = (t_philo *)ft_calloc((n + 1) * sizeof(t_philo), 1);
	if (!ret)
		return (NULL);
	while (i < n)
	{
		ret[i].id = i + 1;
		ret[i].fork1 = &(table->forks[i]);
		ret[i].fork2 = &(table->forks[(i + 1) % n]);
		if (fill_philo(&ret[i], input, table) != true)
		{
			free(ret);
			return (NULL);
		}
		i++;
	}
	return (ret);
}
