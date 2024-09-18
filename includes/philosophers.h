/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:01:49 by anvacca           #+#    #+#             */
/*   Updated: 2024/09/18 14:36:12 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>	// memset
# include <stdio.h>		// printf
# include <stdlib.h>	// malloc, free
# include <unistd.h>	// write, usleep
# include <sys/time.h>	// gettimeofday
# include <pthread.h>	// pthread_create, pthread_detach, pthread_join,
						// pthread_mutex_init, pthread_mutex_destroy
						// pthread_mutex_lock, pthread_mutex_unlock

// Boolean
typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

struct s_stats
{
	unsigned int	nbr_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	cycles;
};

typedef struct s_philo
{
	struct s_stats	stats;
}	t_philo;

//===============================//
//             Utils             //
//===============================//

unsigned int	ft_atoui(char *str);

//===============================//
//             Parser            //
//===============================//

t_bool			check_argc(int ac);
t_bool			check_argv(char **av);

#endif
