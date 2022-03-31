/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:43:38 by gwinnink          #+#    #+#             */
/*   Updated: 2022/03/31 19:04:51 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

static void	fill_philo(t_philo *philo, t_input input)
{
	philo->tt_die = input.tt_die;
	philo->tt_eat = input.tt_eat;
	philo->tt_sleep = input.tt_sleep;
	philo->n_meals = input.n_meals;
}

t_philo	*init_philos(int n, t_flag *forks, t_flag *has_died, t_input input)
{
	t_philo	*ret;
	int		i;

	i = 0;
	ret = (t_philo *)malloc(n * sizeof(t_philo));
	if (!ret)
		return (NULL);
	while (i < n)
	{
		ret[i].id = i + 1;
		ret[i].fork1 = &forks[i];
		ret[i].fork2 = &forks[(i + 1) % n];
		ret[i].has_died = has_died;
		fill_philo(&ret[i], input);
		i++;
	}
	return (ret);
}