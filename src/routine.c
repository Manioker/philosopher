/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:46:08 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/15 13:50:21 by anvacca          ###   ########.fr       */
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

void	*routine(void *args)
{
	t_philos		*philo;
	unsigned int	cycles;

	philo = (t_philos *)args;
	philo_alive(philo, &cycles);
	if (philo->stats->nbr_of_philos == 1)
	{
		ft_wait(philo->stats->time_to_die, philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_think(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->stats->death_note);
		if ((philo->stats->died == 1) || (philo->stats->cycles > 0
				&& cycles-- <= 0))
			break ;
		pthread_mutex_unlock(&philo->stats->death_note);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	if ((philo->stats->died == 1) || (philo->stats->cycles > 0 && cycles <= 0))
		pthread_mutex_unlock(&philo->stats->death_note);
	return (NULL);
}
