/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:07:35 by gwinnink          #+#    #+#             */
/*   Updated: 2022/04/19 10:13:32 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"
#include "time_utils.h"

void	*philo_routine(void *vars)
{
	t_philo	philo;

	philo = *(t_philo *)vars;
	while (1)
	{
		printing(philo, "has taken a fork\n");
		printing(philo, "has taken a fork\n");
		printing(philo, "is eating\n");
		better_usleep(philo.tt_eat * 1000);
		printing(philo, "is sleeping\n");
		better_usleep(philo.tt_sleep * 1000);
		printing(philo, "is thinking\n");
	}
	return (NULL);
}
