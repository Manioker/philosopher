/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:35:35 by anvacca           #+#    #+#             */
/*   Updated: 2024/09/26 13:41:46 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	ft_wait(unsigned int time_to_x, t_philos *philo)
{
	unsigned long	time;

	time = ft_get_time();
	while (ft_get_time() - time < time_to_x)
	{
		pthread_mutex_lock(&philo->stats->death_note);
		if (philo->stats->died == 1)
		{
			pthread_mutex_unlock(&philo->stats->death_note);
			return ;
		}
		pthread_mutex_unlock(&philo->stats->death_note);
		usleep(60);
	}
}
