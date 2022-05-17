/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:16:31 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/17 14:38:05 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdbool.h>

t_flag	create_flag(void)
{
	t_flag	ret;

	ret.flag = 0;
	if (pthread_mutex_init(&ret.mtx, NULL) != 0)
		ret.flag = 1;
	return (ret);
}

void	destroy_flag(t_flag *flag)
{
	if (flag->flag == 0)
		pthread_mutex_destroy(&(flag->mtx));
}

bool	check_flag(t_flag *flag)
{
	bool	ret;

	if (pthread_mutex_lock(&flag->mtx) != 0)
		return (false);
	if (!flag->flag)
		ret = true;
	else
		ret = false;
	if (pthread_mutex_unlock(&flag->mtx) != 0)
		return (false);
	return (ret);
}

bool	flip_flag(t_flag *flag)
{
	if (pthread_mutex_lock(&flag->mtx) != 0)
		return (false);
	if (!flag->flag)
		flag->flag = 1;
	else
		flag->flag = 0;
	if (pthread_mutex_unlock(&flag->mtx) != 0)
		return (false);
	return (true);
}

bool	decrement_flag(t_flag *flag)
{
	if (pthread_mutex_lock(&flag->mtx) != 0)
		return (false);
	flag->flag--;
	if (pthread_mutex_unlock(&flag->mtx) != 0)
		return (false);
	return (true);
}
