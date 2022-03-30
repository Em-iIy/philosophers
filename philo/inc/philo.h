/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:50 by gwinnink          #+#    #+#             */
/*   Updated: 2022/03/30 16:58:26 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// ----------------------------------------Colors
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define PURPLE "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"
# define NORMAL "\033[0m"

// ----------------------------------------Includes
# include <stdlib.h>

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
int		error_msg(const char *msg);

// ------------------------------Parsing
t_input	parsing(int argc, char **argv);

#endif