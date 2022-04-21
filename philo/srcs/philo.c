/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:54 by gwinnink          #+#    #+#             */
/*   Updated: 2022/04/21 14:20:55 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "not_libft.h"
#include "time_utils.h"
#include <stdlib.h>

void	join(t_philo *threads)
{
	int	i;

	i = 0;
	while (threads[i].thread)
	{
		pthread_join(threads[i].thread, NULL); // error prone
		i++;
	}
	free(threads);
}

int	main(int argc, char **argv)
{
	t_input	input;
	t_table	table;
	int		i;

	if (argc != 5 && argc != 6)
		return (error_msg("error: input: invalid amount of arguments\n\
Usage: ./philo [number of philosophers] [tt. die] [tt. eat] \
[tt. sleep] opt. [number of meals]\n"));
	input = parsing(argc, argv);
	if (!input.valid)
		return (error_msg("error: input: input not valid integer\n"));
	if (init_table(&table, input) == -1)
		return (error_msg("error: pthread: init failed\n"));
	for (i = 0; i < input.n_philo; i++)
		table.forks[i].flag = i + 1;
	join(table.philos);
}
