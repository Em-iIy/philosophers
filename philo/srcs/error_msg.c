/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:10:54 by gwinnink          #+#    #+#             */
/*   Updated: 2022/04/13 17:18:03 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "not_libft.h"
#include <unistd.h>
#include <stdlib.h>

static char	*s_cpy(char *ret, const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	return (&ret[i]);
}

static char	*add_color(const char *color, const char *msg)
{
	char	*ret;
	int		i;
	int		j;
	int		final_len;

	i = 0;
	j = 0;
	final_len = ft_strlen(color) + ft_strlen(msg) + 4;
	ret = (char *)malloc(final_len + 1);
	if (!ret)
		return (NULL);
	ret[final_len] = 0;
	if (s_cpy(s_cpy(s_cpy(ret, color), msg), NORMAL) - final_len != ret)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

int	error_msg(const char *msg)
{
	char	*temp;

	temp = add_color(RED, msg);
	if (!temp)
		return (2);
	write(2, temp, ft_strlen(temp));
	return (1);
}
