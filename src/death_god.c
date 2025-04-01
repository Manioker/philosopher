/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_god.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:42:45 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/22 11:23:18 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned int	ate(t_philos *philos)
{
	unsigned int	i;

	i = 0;
	while (philos[i].meal >= philos->stats->cycles
		&& i < philos->stats->nbr_of_philos)
		i++;
	if (i == philos->stats->nbr_of_philos)
	{
		philos->stats->died = 1;
		pthread_mutex_unlock(&philos->stats->death_note);
		return (0);
	}
	return (1);
}

void	*death_god(void *args)
{
	t_philos		*philo;
	unsigned int	i;

	philo = (t_philos *)args;
	while (true)
	{
		i = -1;
		usleep(20);
		while (++i < philo->stats->nbr_of_philos)
		{
			pthread_mutex_lock(&philo->stats->death_note);
			if (ft_get_time()
				- philo[i].death_timer > philo->stats->time_to_die)
			{
				philo->stats->died = 1;
				printf("\e[31m%lu %u died\n", ft_get_time()
					- philo->stats->time_start, philo[i].id);
				pthread_mutex_unlock(&philo->stats->death_note);
				return (NULL);
			}
			if (ate(philo) == 0)
				return (NULL);
			pthread_mutex_unlock(&philo->stats->death_note);
		}
	}
}
