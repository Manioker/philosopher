/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:46:08 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/15 15:11:19 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	philo_alive(t_philos *philo, unsigned int *cycles)
{
	*cycles = philo->stats->cycles;
	pthread_mutex_lock(&philo->stats->death_note);
	philo->is_dead = 0;
	pthread_mutex_unlock(&philo->stats->death_note);
}

static void	*one_philo(t_philos *philo)
{
	write(1, "0 1 is thinking\n", 16);
	usleep(philo->stats->time_to_die * 1000);
	printf("\e[31m%lu 1 died\n", ft_get_time() - philo->stats->time_start);
	return (NULL);
}

static void	hyper_loop(t_philos *philo, unsigned int *cycles)
{
	while (1)
	{
		pthread_mutex_lock(&philo->stats->death_note);
		if (philo->stats->died == 1)
			return ;
		pthread_mutex_unlock(&philo->stats->death_note);
		ft_eat(philo);
		pthread_mutex_lock(&philo->stats->death_note);
		if (philo->stats->cycles > 0 && *cycles <= 0)
			return ;
		pthread_mutex_unlock(&philo->stats->death_note);
		ft_sleep(philo);
		ft_think(philo);
		*cycles -= 1;
	}
}

void	*routine(void *args)
{
	t_philos		*philo;
	unsigned int	cycles;

	philo = (t_philos *)args;
	philo_alive(philo, &cycles);
	if (philo->stats->nbr_of_philos == 1)
		return (one_philo(philo));
	if (philo->id % 2 == 0)
	{
		printf("0 %u is thinking\n", philo->id);
		usleep(1000);
	}
	hyper_loop(philo, &cycles);
	if ((philo->stats->died == 1) || (philo->stats->cycles > 0 && cycles <= 0))
		pthread_mutex_unlock(&philo->stats->death_note);
	return (NULL);
}
