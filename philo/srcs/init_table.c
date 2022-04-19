/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:29:49 by gwinnink          #+#    #+#             */
/*   Updated: 2022/04/19 10:04:51 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "flag_utils.h"
#include "time_utils.h"

int	init_table(t_table *table, t_input input)
{
	int	i;

	i = 0;
	table->has_died = create_flag();
	table->printing = create_flag();
	table->forks = init_forks(input.n_philo);
	table->start_time = 0;
	if (!table->forks)
		return (-1);
	table->philos = init_philos(input.n_philo, table, input);
	if (!table->philos)
	{
		clear_forks(table->forks, input.n_philo);
		return (-1);
	}
	table->start_time = get_time();
	while (i < input.n_philo)
	{
		pthread_create(&table->philos[i].thread, NULL, &philo_routine, \
			(void *)&(table->philos[i]));
		i++;
	}
	return (0);
}
