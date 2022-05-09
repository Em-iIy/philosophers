/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:45:48 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/09 18:43:22 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "time_utils.h"
#include "not_libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

static char	*itoa_cpy(char *str, int n)
{
	char	*num;
	int		i;

	num = ft_itoa(n);
	if (!num)
		return (NULL);
	i = 0;
	while (num[i])
	{
		*str = num[i];
		str++;
		i++;
	}
	free(num);
	*str = ' ';
	str++;
	*str = 0;
	return (str);
}

static char	*fill_num(char *origin, char *str, int n1, int n2)
{
	str = itoa_cpy(str, n1);
	if (!str)
	{
		free(origin);
		return (NULL);
	}
	str = itoa_cpy(str, n2);
	if (!str)
	{
		free(origin);
		return (NULL);
	}
	return (str);
}

uint64_t	printing(t_philo philo, uint64_t *eat, \
							const char *msg, int dead)
{
	char		*print_str;
	char		*ptr;
	uint64_t	time;
	int			msg_len;

	time = get_time();
	if (eat)
		*eat = time;
	print_str = (char *)ft_calloc(44, sizeof(char));
	if (!print_str)
		return (0);
	ptr = print_str;
	msg_len = ft_strlen(msg);
	ptr += ft_strlcpy(print_str, RED, 9);
	print_str[5] = ((philo.id % 7) + 1) + '0';
	pthread_mutex_lock(&(philo.printing->mtx));
	time = get_time();
	if (eat)
		*eat = time;
	ptr = fill_num(print_str, ptr, (time - *philo.start_time) / 1000, \
					philo.id);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, msg, msg_len + 1);
	if (!philo.has_died->flag || dead)
		write(1, print_str, 44);
	pthread_mutex_unlock(&(philo.printing->mtx));
	free(print_str);
	return (time);
}
