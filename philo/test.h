/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:22:40 by gwinnink          #+#    #+#             */
/*   Updated: 2022/04/07 16:00:26 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <pthread.h>
# include <sys/time.h>

# define DELAY 100000

typedef struct s_flag
{
	pthread_mutex_t	mtx;
	int				flag;
}	t_flag;

typedef struct s_mails
{
	t_flag			mails;
	t_flag			printing;
	struct timeval	time;
	
}	t_mails;


typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			loops;
	t_mails		*mails;
}	t_philo;

int    ft_usleep(suseconds_t sleep_time);

#endif