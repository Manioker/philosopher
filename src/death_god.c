/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_god.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:42:45 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/14 15:20:04 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*death_god(void *args)
{
	t_philos		*philo;
	unsigned int	i;

	philo = (t_philos *)args;
	while (true)
	{
		i = 0;
		pthread_mutex_lock(&philo->stats->death_note);
		if (philo->stats->god_died == 1)
		{
			pthread_mutex_unlock(&philo->stats->death_note);
			break ;
		}
		while (i < philo->stats->nbr_of_philos)
		{
			if (philo[i].is_dead == 1)
			{
				philo->stats->died = 1;
				printf("\e[31m%lu %u died\n", ft_get_time()
					- philo->stats->time_start, philo[i].id);
				pthread_mutex_unlock(&philo->stats->death_note);
				return (NULL);
			}
			i++;
		}
		pthread_mutex_unlock(&philo->stats->death_note);
	}
	return (NULL);
}
