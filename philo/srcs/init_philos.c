/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:43:38 by gwinnink          #+#    #+#             */
/*   Updated: 2022/04/21 13:45:06 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "not_libft.h"
#include <stdlib.h>
#include <pthread.h>

static void	fill_philo(t_philo *philo, t_input input)
{
	philo->tt_die = input.tt_die;
	philo->tt_eat = input.tt_eat;
	philo->tt_sleep = input.tt_sleep;
	philo->n_meals = input.n_meals;
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
		ret[i].has_died = &(table->has_died);
		ret[i].printing = &(table->printing);
		ret[i].start_time = &(table->start_time);
		ret[i].last_meal = 0;
		fill_philo(&ret[i], input);
		i++;
	}
	return (ret);
}
