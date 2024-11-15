/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:24:48 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/15 13:25:41 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->stats->death_note);
	if (philo->stats->died == 0 && philo->is_dead == 0)
		printf("%lu %u is sleeping\n", ft_get_time() - philo->stats->time_start,
			philo->id);
	pthread_mutex_unlock(&philo->stats->death_note);
	ft_wait(philo->stats->time_to_sleep, philo);
}
