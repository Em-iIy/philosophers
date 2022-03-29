/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:50 by gwinnink          #+#    #+#             */
/*   Updated: 2022/03/29 14:17:41 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// ----------------------------------------Includes
# include <stdlib.h>
# include <stdio.h>

// ----------------------------------------Enums

// ----------------------------------------Structs
typedef struct s_input
{
	int	n_philo;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	n_meals;
	int	valid;
}	t_input;

// ----------------------------------------Prototypes
// ------------------------------Error exit

// ------------------------------Parsing
t_input	parsing(int argc, char **argv);

// ------------------------------Children

// ------------------------------Libft utils

#endif