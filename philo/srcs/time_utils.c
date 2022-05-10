/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:02:32 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/10 16:02:53 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

// Returns current time in micro seconds
uint64_t	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	return (t.tv_usec + t.tv_sec * 1000000);
}

void	better_usleep(uint64_t n)
{
	uint64_t	start;

	start = get_time();
	while (n >= get_time() - start)
		usleep(250);
}
