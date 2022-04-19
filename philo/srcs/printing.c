/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:45:48 by gwinnink          #+#    #+#             */
/*   Updated: 2022/04/19 10:17:29 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "time_utils.h"
#include "not_libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

static int	itoa_cpy(char *origin, char *str, int n1, int n2)
{
	char	*num;
	int		len;

	num = ft_itoa(n1);
	if (!num)
	{
		free(origin);
		return (0);
	}
	len = ft_strlcpy(str, num, ft_strlen(num) + 1) + 1;
	str[len - 1] = ' ';
	free(num);
	num = ft_itoa(n2);
	if (!num)
	{
		free(origin);
		return (0);
	}
	len += ft_strlcpy(str + len, num, ft_strlen(num) + 1) + 1;
	str[len - 1] = ' ';
	free(num);
	return (len);
}

int	printing(t_philo philo, const char *msg)
{
	char	*print_str;
	char	*ptr;
	int		len;
	int		msg_len;

	len = 0;
	print_str = (char *)malloc(44 * sizeof(char));
	if (!print_str)
		return (0);
	ptr = print_str;
	msg_len = ft_strlen(msg);
	ptr += ft_strlcpy(print_str, RED, 9);
	print_str[5] = ((philo.id % 7) + 1) + '0';
	pthread_mutex_lock(&(philo.printing->mtx));
	len = itoa_cpy(print_str, ptr, (get_time() - *philo.start_time) / 1000, \
					philo.id);
	if (!len)
		return (0);
	ptr += len;
	len += ft_strlcpy(ptr, msg, msg_len + 1);
	write(1, print_str, ft_strlen(print_str));
	pthread_mutex_unlock(&(philo.printing->mtx));
	free(print_str);
	return (1);
}
