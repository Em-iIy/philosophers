/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:22:42 by gwinnink          #+#    #+#             */
/*   Updated: 2022/03/30 20:52:08 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_atoi(const char *str)
{
	long	ret_int;
	int		i;

	ret_int = 0;
	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (-1);
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret_int *= 10;
		ret_int += str[i] - '0';
		if (ret_int > INT_MAX)
			return (-1);
		i++;
	}
	return (ret_int);
}

void	join(t_philo *threads)
{
	int	i;

	i = 0;
	while (threads[i].thread)
	{
		pthread_join(threads[i].thread, NULL);
		i++;
	}
	free(threads);
}

void	*routine(void *vars)
{
	t_philo	b;
	int		a;

	b = *((t_philo *)vars);
	a = b.id;
	printf("%d:\tHello from thread\n", a);
	for (int i = 0; i < b.loops; i++)
	{
		pthread_mutex_lock(&b.mails->mutex);
		b.mails->mails += 1;
		pthread_mutex_unlock(&b.mails->mutex);
	}
	printf("%d:\tBye from thread\n", a);
	return (vars);
}

int	main(int argc, char **argv)
{
	t_philo		*threads;
	int			thread_count;
	int			i;
	t_mails		mails;

	i = 0;
	mails.mails = 0;
	pthread_mutex_init(&mails.mutex, NULL);
	if (argc != 3)
		return (1);
	thread_count = ft_atoi(1[argv]);
	threads = (t_philo *)calloc((thread_count + 1), sizeof(t_philo));
	if (!threads)
		return (1);
	while (i < thread_count)
	{
		threads[i].id = i;
		threads[i].mails = &mails;
		threads[i].loops = ft_atoi(2[argv]);
		if (pthread_create(&threads[i].thread, NULL, &routine, &threads[i]) != 0)
		{
			threads[i].thread = NULL;
			join(threads);
		}
		i++;
	}
	join(threads);
	printf("\n%d\n", mails.mails);
	return (0);
}
