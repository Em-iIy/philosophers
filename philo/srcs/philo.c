/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:54 by gwinnink          #+#    #+#             */
/*   Updated: 2022/03/30 17:13:49 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_input	input;

	if (argc != 5 && argc != 6)
		return (error_msg("error: input: invalid amount of arguments\n\
Usage: ./philo [number of philosophers] [tt. die] [tt. eat] \
[tt. sleep] opt. [number of meals]\n"));
	input = parsing(argc, argv);
	if (!input.valid)
		return (error_msg("error: input: input not valid integer\n"));
}
