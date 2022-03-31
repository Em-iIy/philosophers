/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:48:31 by gwinnink          #+#    #+#             */
/*   Updated: 2022/03/31 15:40:45 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

t_flag	*init_forks(int n)
{
	t_flag	*ret;
	int		i;

	i = 0;
	ret = (t_flag *)malloc(n * sizeof(t_flag));
	if (!ret)
		return (NULL);
	while (i < n)
	{
		ret[i] = create_flag();
		if (ret[i].flag == 1)
			return (clear_forks(ret, n));
		i++;
	}
	return (ret);
}
