/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:29:49 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/09 18:13:21 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "flag_utils.h"
#include "time_utils.h"
#include <unistd.h>

int	init_table(t_table *table, t_input input)
{
	int	i;

	i = 0;
	table->start_time = 0;
	table->has_died = create_flag(); // error prone
	table->printing = create_flag(); // error prone
	table->forks = init_forks(input.n_philo);
	if (!table->forks)
		return (-1);
	table->philos = init_philos(input.n_philo, table, input);
	if (!table->philos)
	{
		clear_forks(table->forks, input.n_philo);
		return (-1);
	}
	while (i < input.n_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &philo_routine, \
			(void *)&(table->philos[i])) != 0)
		{
			table->philos[i].thread = NULL;
			return (0);
		}
		i++;
	}
	usleep(1000000);
	table->start_time = get_time();
	return (0);
}
