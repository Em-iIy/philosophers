/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwinnink <gwinnink@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:48:50 by gwinnink          #+#    #+#             */
/*   Updated: 2022/05/17 15:06:02 by gwinnink         ###   ########.fr       */
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
// # define DEBUG(id,msg) printf("\033[0m%s:%d    \t%-17sphilo %d:\t%-40s\033[0m\n", __FILE__, __LINE__, __func__, id, msg)
// # ifndef DEBUG
// #  define DEBUG(id,msg)
// # endif
// ----------------------------------------Includes
# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdio.h> // remove

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

typedef struct s_flag
{
	pthread_mutex_t	mtx;
	int				flag;
}	t_flag;

typedef struct s_philo
{
	int			id;
	t_flag		*fork1;
	t_flag		*fork2;
	t_flag		*has_died;
	t_flag		*printing;
	t_flag		*done_eating;
	t_flag		n_meals;
	t_flag		lm_flag;
	uint64_t	*last_meal;
	uint64_t	*start_time;
	int			tt_die;
	int			tt_eat;
	int			tt_sleep;
	pthread_t	thread;
}	t_philo;

typedef struct s_table
{
	t_flag		*forks;
	t_flag		has_died;
	t_philo		*philos;
	t_flag		printing;
	t_flag		done_eating;
	uint64_t	start_time;
	int			n_philo;
	int			tt_die;
}	t_table;

// ----------------------------------------Prototypes
// ------------------------------Error exit
int				error_msg(const char *msg);

// ------------------------------Parsing
t_input			parsing(int argc, char **argv);

// ------------------------------Init
int				init_table(t_table *table, t_input input);
t_flag			*init_forks(int n);
t_philo			*init_philos(int n, t_table *table, t_input input);
// --------------------Init Utils
void			*clear_forks(t_flag *forks, int n);

// ------------------------------Philo routine
void			*philo_routine(void *vars);
void			*philo_monitor(void *vars);
void			*single_philo_monitor(void *vars);

// ------------------------------Philo state
bool			grab_fork(t_philo *philo, t_flag *fork);
bool			eat(t_philo *philo);
bool			philo_sleep(t_philo *philo);
bool			think(t_philo *philo);
bool			die(t_philo *philo);

#endif