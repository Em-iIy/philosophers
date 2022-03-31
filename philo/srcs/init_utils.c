/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:58:01 by gwinnink          #+#    #+#             */
/*   Updated: 2022/03/31 16:06:10 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

t_flag	create_flag(void)
{
	t_flag	ret;

	ret.flag = 0;
	if (pthread_mutex_init(&ret.mtx, NULL) != 0)
		ret.flag = 1;
	return (ret);
}

void	destroy_flag(t_flag flag)
{
	if (flag.flag == 0)
		pthread_mutex_destroy(&flag.mtx);
}

void	*clear_forks(t_flag *forks, int n)
{
	int	i;

	i = 0;
	while (forks[i].flag != 1 && i < n)
	{
		destroy_flag(forks[i]);
		i++;
	}
	free(forks);
	return (NULL);
}
