/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:23:52 by gwinnink          #+#    #+#             */
/*   Updated: 2022/03/29 14:21:13 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

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

t_input	parsing(int argc, char **argv)
{
	t_input	ret;

	ret.n_philo = ft_atoi(argv[1]);
	ret.tt_die = ft_atoi(argv[2]);
	ret.tt_eat = ft_atoi(argv[3]);
	ret.tt_sleep = ft_atoi(argv[4]);
	ret.n_meals = -2;
	if (argc == 6)
		ret.n_meals = ft_atoi(argv[5]);
	printf("n_philo: %d\n", ret.n_philo);
	printf("tt_die: %d\n", ret.tt_die);
	printf("tt_eat: %d\n", ret.tt_eat);
	printf("tt_sleep: %d\n", ret.tt_sleep);
	printf("n_meals: %d\n", ret.n_meals);
	ret.valid = 1;
	if (ret.n_philo < 0 || ret.tt_die < 0 || ret.tt_eat < 0 || \
				ret.tt_sleep < 0 || ret.n_meals == -1)
		ret.valid = 0;
	return (ret);
}
