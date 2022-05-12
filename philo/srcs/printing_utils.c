/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:45:48 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/12 17:44:47 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "time_utils.h"
#include "flag_utils.h"
#include <pthread.h>

bool	printing(t_philo *philo, int eat, const char *msg)
{
	uint64_t	time;

	time = get_time();
	if (eat)
		*philo->last_meal = time;
	if (check_flag(philo->has_died))
	{
		printf("\033[0;9%cm %llu %d %s\n", (philo->id % 7) + 1 + '0', \
			(time - *philo->start_time) / 1000, philo->id, msg);
		return (true);
	}
	return (false);
}
