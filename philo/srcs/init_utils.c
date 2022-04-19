/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:58:01 by gwinnink          #+#    #+#             */
/*   Updated: 2022/04/13 15:58:58 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "flag_utils.h"
#include <stdlib.h>
#include <pthread.h>

void	*clear_forks(t_flag *forks, int n)
{
	int	i;

	i = 0;
	while (forks[i].flag != 1 && i < n)
	{
		destroy_flag(&forks[i]);
		i++;
	}
	free(forks);
	return (NULL);
}
