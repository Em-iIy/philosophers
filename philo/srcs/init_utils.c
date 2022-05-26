/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:58:01 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/26 17:15:08 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "flag_utils.h"
#include <stdlib.h>

void	*clear_forks(t_flag *forks, int n)
{
	int	i;

	i = 0;
	while (i < n && forks[i].flag != 1)
	{
		destroy_flag(&forks[i]);
		i++;
	}
	free(forks);
	return (NULL);
}
