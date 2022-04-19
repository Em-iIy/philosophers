/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:16:31 by gwinnink          #+#    #+#             */
/*   Updated: 2022/04/13 15:50:49 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

t_flag	create_flag(void)
{
	t_flag	ret;

	ret.flag = 0;
	if (pthread_mutex_init(&ret.mtx, NULL) != 0)
		ret.flag = 1;
	return (ret);
}

void	lock_flag(t_flag *flag)
{
	if (flag->flag)
		return ;
	pthread_mutex_lock(&(flag->mtx));
	flag->flag = 1;
}

void	unlock_flag(t_flag *flag)
{
	if (!(flag->flag))
		return ;
	pthread_mutex_unlock(&(flag->mtx));
	flag->flag = 0;
}

void	destroy_flag(t_flag *flag)
{
	if (flag->flag == 0)
		pthread_mutex_destroy(&(flag->mtx));
}
