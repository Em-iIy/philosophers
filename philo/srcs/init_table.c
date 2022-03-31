/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:29:49 by gwinnink          #+#    #+#             */
/*   Updated: 2022/03/31 15:56:07 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table, t_input input)
{
	table->has_died = create_flag();
	table->forks = init_forks(input.n_philo);
	if (!table->forks)
		return (-1);
	table->philos = init_philos(input.n_philo, table->forks, \
		&table->has_died, input);
	if (!table->philos)
	{
		clear_forks(table->forks, input.n_philo);
		return (-1);
	}
	return (0);
}