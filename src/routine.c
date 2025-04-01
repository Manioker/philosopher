/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:46:08 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/22 11:09:36 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	*one_philo(t_philos *philo)
{
	write(1, "0 1 is thinking\n", 16);
	usleep(philo->stats->time_to_die * 1000);
	printf("\e[31m%lu 1 died\n", ft_get_time() - philo->stats->time_start);
	return (NULL);
}

static void	hyper_loop(t_philos *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->stats->death_note);
		ft_think(philo);
		if (philo->stats->died == 1)
		{
			pthread_mutex_unlock(&philo->stats->death_note);
			return ;
		}
		pthread_mutex_unlock(&philo->stats->death_note);
		ft_eat(philo);
		ft_sleep(philo);
	}
}

void	*routine(void *args)
{
	t_philos		*philo;

	philo = (t_philos *)args;
	if (philo->stats->nbr_of_philos == 1)
		return (one_philo(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	hyper_loop(philo);
	return (NULL);
}
