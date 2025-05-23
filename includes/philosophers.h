/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:49 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/22 11:22:06 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>  // pthread_create, pthread_detach, pthread_join,
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free
# include <string.h>   // memset
# include <sys/time.h> // gettimeofday
# include <unistd.h>   // write, usleep
						// pthread_mutex_init, pthread_mutex_destroy
						// pthread_mutex_lock, pthread_mutex_unlock

// Boolean
typedef enum e_bool
{
	false = 0,
	true = 1
}					t_bool;

struct				s_stats
{
	unsigned int	nbr_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_think;
	unsigned int	cycles;
	unsigned int	philo_cycles;
	unsigned long	time_start;
	unsigned int	died;
	unsigned int	god_died;
	pthread_mutex_t	death_note;
};

typedef struct s_philos
{
	pthread_t		thread;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	unsigned int	id;
	unsigned int	meal;
	unsigned long	death_timer;
	struct s_stats	*stats;
}					t_philos;

typedef struct s_gen
{
	pthread_t		god;
	struct s_stats	philo_stats;
	struct s_philos	philos[200];
}					t_gen;

// UTILS
unsigned int		ft_atoui(char *str);
unsigned long		ft_get_time(void);
void				ft_wait(unsigned int time_to_x, t_philos *philo);

// PARSING
t_bool				parsing(int ac, char **av);

// GENERAL
void				*routine(void *args);
void				ft_sleep(t_philos *philo);
void				ft_eat(t_philos *philo);
void				ft_think(t_philos *philo);
void				*death_god(void *args);

#endif
