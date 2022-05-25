/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:26:58 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/25 10:27:34 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

void	*ft_calloc(int count, size_t size)
{
	char			*ret;

	ret = (char *)malloc(count * size);
	if (!ret)
		return (NULL);
	return (memset(ret, 0, count * size));
}
