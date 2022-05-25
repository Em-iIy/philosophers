/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:29:49 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/25 10:32:01 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "flag_utils.h"
#include "time_utils.h"
#include <pthread.h>
#include <unistd.h>

// void	*fork_status(void *vars)
// {
// 	t_table	table;

// 	table = *(t_table *)vars;
// 	while (1)
// 	{
// 		sleep(10);
// 		for (int i = 0; i < table.n_philo; i++)
// 		{
// 			if (pthread_mutex_trylock(&table.forks[i].mtx) == 0)
// 			{
// 				printf("fork: %d\t %sUNLOCKED%s\n", i, GREEN, NORMAL);
// 				pthread_mutex_unlock(&table.forks[i].mtx);
// 			}
// 			else
// 				printf("fork: %d\t %sLOCKED%s\n", i, RED, NORMAL);
// 		}
// 	}
// }

static bool	fill_table(t_table *table, t_input input)
{
	table->start_time = 0;
	table->n_philo = input.n_philo;
	table->tt_die = input.tt_die;
	table->has_died = create_flag();
	table->done_eating = create_flag();
	table->printing = create_flag();
	table->forks = init_forks(input.n_philo);
	if (!table->forks || table->has_died.flag == 1 || \
		table->done_eating.flag == 1 || table->printing.flag == 1)
		return (false);
	table->done_eating.flag = input.n_philo;
	table->philos = init_philos(input.n_philo, table, input);
	if (!table->philos)
	{
		clear_forks(table->forks, input.n_philo);
		return (false);
	}
	return (true);
}

static bool	start_philo(t_table *table)
{
	int			i;

	i = 0;
	while (i < table->n_philo)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &philo_routine, \
			(void *)&(table->philos[i])) != 0)
		{
			table->philos[i].thread = 0;
			return (false);
		}
		i++;
	}
	return (true);
}

int	init_table(t_table *table, t_input input)
{
	pthread_t	monitor;

	if (fill_table(table, input) != true)
		return (-1);
	if (start_philo(table) != true)
		return (-1);
	usleep(100000);
	pthread_mutex_lock(&table->printing.mtx);
	table->start_time = get_time();
	if (table->start_time == 0)
	{
		table->start_time = 1;
		table->has_died.flag = 1;
	}
	pthread_mutex_unlock(&table->printing.mtx);
	pthread_create(&monitor, NULL, &single_philo_monitor, (void *)table);
	pthread_join(monitor, NULL);
	return (0);
}
