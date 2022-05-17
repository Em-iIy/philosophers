/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:15:26 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/10 16:41:30 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG_UTILS_H
# define FLAG_UTILS_H

# include "philo.h"

// ----------------------------------------Prototypes
t_flag	create_flag(void);
void	destroy_flag(t_flag *flag);
bool	check_flag(t_flag *flag);
bool	flip_flag(t_flag *flag);
bool	decrement_flag(t_flag *flag);

#endif