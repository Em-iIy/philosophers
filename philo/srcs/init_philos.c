/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:43:38 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/17 15:08:04 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "not_libft.h"
#include "flag_utils.h"
#include <stdlib.h>
#include <pthread.h>

static void	fill_philo(t_philo *philo, t_input input)
{
	philo->tt_die = input.tt_die;
	philo->tt_eat = input.tt_eat;
	philo->tt_sleep = input.tt_sleep;
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
		ret[i].done_eating = &(table->done_eating);
		ret[i].start_time = &(table->start_time);
		ret[i].last_meal = 0;
		ret[i].lm_flag = create_flag();
		ret[i].n_meals = create_flag();
		if (ret[i].lm_flag.flag == 1 || ret[i].n_meals.flag == 1)
		{
			free(ret);
			return (NULL);
		}
		ret[i].n_meals.flag = input.n_meals;
		fill_philo(&ret[i], input);
		i++;
	}
	return (ret);
}
