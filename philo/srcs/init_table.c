/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:29:49 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/16 15:48:19 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "flag_utils.h"
#include "time_utils.h"
#include <unistd.h>
#include <pthread.h>

void	*fork_status(void *vars)
{
	t_table	table;

	table = *(t_table *)vars;
	while (1)
	{
		sleep(10);
		for (int i = 0; i < 200; i++)
		{
			if (pthread_mutex_trylock(&table.forks[i].mtx) == 0)
			{
				printf("fork: %d\t %sUNLOCKED%s\n", i, GREEN, NORMAL);
				pthread_mutex_unlock(&table.forks[i].mtx);
			}
			else
				printf("fork: %d\t %sLOCKED%s\n", i, RED, NORMAL);
		}
	}
}

int	init_table(t_table *table, t_input input)
{
	int	i;
	// pthread_t fork_stat;

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
	pthread_mutex_lock(&table->printing.mtx);
	table->start_time = get_time();
	pthread_mutex_unlock(&table->printing.mtx);
	// if (input.n_philo == 200)
	// {
	// 	pthread_create(&fork_stat, NULL, &fork_status, (void *)table);
	// }
	return (0);
}
