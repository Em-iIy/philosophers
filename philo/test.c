/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:22:42 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/09 18:42:12 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

t_flag	create_flag(void)
{
	t_flag	ret;

	ret.flag = 0;
	if (pthread_mutex_init(&ret.mtx, NULL) != 0)
		ret.flag = 1;
	return (ret);
}

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

uint64_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_usec + t.tv_sec * 1000000);
}

void	better_usleep(uint64_t n)
{
	uint64_t	start;

	start = get_time();
	while (n >= get_time() - start)
		usleep(250);
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
	struct timeval	t1;
	struct timeval	t2;

	b = *((t_philo *)vars);
	// gettimeofday(&t1, NULL);
	// better_usleep(DELAY);
	// gettimeofday(&t2, NULL);
	// printf("ft slept1: %ld usec\n", (t2.tv_usec - t1.tv_usec) + (t2.tv_sec - t1.tv_sec) * 1000000);
	// gettimeofday(&t1, NULL);
	// better_usleep(DELAY);
	// gettimeofday(&t2, NULL);
	// printf("ft slept2: %ld usec\n", (t2.tv_usec - t1.tv_usec) + (t2.tv_sec - t1.tv_sec) * 1000000);
	// gettimeofday(&t1, NULL);
	// usleep(DELAY);
	// gettimeofday(&t2, NULL);
	// printf("normal slept1: %ld usec\n", (t2.tv_usec - t1.tv_usec) + (t2.tv_sec - t1.tv_sec) * 1000000);
	// gettimeofday(&t1, NULL);
	// usleep(DELAY);
	// gettimeofday(&t2, NULL);
	// printf("normal slept2: %ld usec\n", (t2.tv_usec - t1.tv_usec) + (t2.tv_sec - t1.tv_sec) * 1000000);
	a = b.id;
	// while (1)
	// {
	// 	if (!b.mails->printing.flag)
	// 	{
			pthread_mutex_lock(&b.mails->printing.mtx);
	// 		b.mails->printing.flag++;
			gettimeofday(&t1, NULL);
			printf("[%ld]\t%d:\tHello from thread\n",((t1.tv_sec - b.mails->time.tv_sec) * 1000) + ((t1.tv_usec - b.mails->time.tv_usec) / 1000), a);
			// b.mails->printing.flag--;
			pthread_mutex_unlock(&b.mails->printing.mtx);
	// 		break ;
	// 	}
	// }
	for (int i = 0; i < b.loops; i++)
	{
		pthread_mutex_lock(&b.mails->mails.mtx);
		b.mails->mails.flag += 1;
		pthread_mutex_unlock(&b.mails->mails.mtx);
	}
	// while (1)
	// {
	// 	if (!b.mails->printing.flag)
	// 	{
			pthread_mutex_lock(&b.mails->printing.mtx);
			// b.mails->printing.flag++;
			gettimeofday(&t2, NULL);
			printf("[%ld]\t%d:\tBye from thread\t\t\t(tv_sec diff:%ld)\t(tv_usec diff:%d)\n",((t2.tv_sec - b.mails->time.tv_sec) * 1000) + ((t2.tv_usec - b.mails->time.tv_usec) / 1000), a, t2.tv_sec - b.mails->time.tv_sec, t2.tv_usec - b.mails->time.tv_usec);
			// b.mails->printing.flag--;
			pthread_mutex_unlock(&b.mails->printing.mtx);
	// 		break ;
	// 	}
	// }
	return (vars);
}

int	main(int argc, char **argv)
{
	t_philo		*threads;
	int			thread_count;
	int			i;
	t_mails		mails;

	i = 0;
	mails.mails = create_flag();
	mails.printing = create_flag();
	if (argc != 3)
		return (1);
	thread_count = ft_atoi(1[argv]);
	threads = (t_philo *)calloc((thread_count + 1), sizeof(t_philo));
	if (!threads)
		return (1);
	gettimeofday(&mails.time, NULL);
	printf("time:%ld.%d\n", mails.time.tv_sec, mails.time.tv_usec);
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
	printf("\n%d\n", mails.mails.flag);
	gettimeofday(&mails.time, NULL);
	printf("time:%ld.%d\n", mails.time.tv_sec, mails.time.tv_usec);
	printf("time:%ld\n", get_time());
	return (0);
}
