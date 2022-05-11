/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:25:58 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/11 16:35:46 by gwinnink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_UTILS_H
# define TIME_UTILS_H

// ----------------------------------------Prototypes
uint64_t	check_time_stamp(pthread_mutex_t *mtx, uint64_t *num);
uint64_t	get_time(void);
void		better_usleep(uint64_t n);

#endif
