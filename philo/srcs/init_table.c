/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:29:49 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/24 19:09:01 by gwinnink         ###   ########.fr       */
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
		for (int i = 0; i < table.n_philo; i++)
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
	int			i;
	pthread_t	fork_stat;

	i = 0;
	table->start_time = 0;
	table->has_died = create_flag(); // error prone
	table->done_eating = create_flag(); // error prone
	table->done_eating.flag = input.n_philo;
	table->printing = create_flag(); // error prone
	table->forks = init_forks(input.n_philo);
	table->n_philo = input.n_philo;
	table->tt_die = input.tt_die;
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
			table->philos[i].thread = 0;
			return (0);
		}
		i++;
	}
	usleep(1000000);
	pthread_mutex_lock(&table->printing.mtx);
	// table->start_time = get_time();
	if (table->start_time == 0)
	{
		table->start_time = 1;
		table->has_died.flag = 1;
	}
	pthread_mutex_unlock(&table->printing.mtx);
	pthread_create(&fork_stat, NULL, &single_philo_monitor, (void *)table);
	pthread_join(fork_stat, NULL);
	return (0);
}
