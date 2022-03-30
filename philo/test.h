/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:22:40 by gwinnink          #+#    #+#             */
/*   Updated: 2022/03/30 20:47:53 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include <pthread.h>

typedef struct s_mails
{
	pthread_mutex_t	mutex;
	int				mails;
}	t_mails;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			loops;
	t_mails		*mails;
}	t_philo;


#endif