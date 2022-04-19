/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:15:26 by gwinnink          #+#    #+#             */
/*   Updated: 2022/04/13 15:53:09 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG_UTILS_H
# define FLAG_UTILS_H

# include "philo.h"

// ----------------------------------------Prototypes
t_flag	create_flag(void);
void	lock_flag(t_flag *flag);
void	unlock_flag(t_flag *flag);
void	destroy_flag(t_flag *flag);

#endif