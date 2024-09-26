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
		if (ft_get_time() - philo->death_timer > philo->stats->time_to_die)
		{
			pthread_mutex_lock(&philo->stats->death_note);
			printf("\e[31mcurrent time %lu || philo %u died\n", ft_get_time()
			- philo->stats->time_start , philo->id);
			philo->stats->died = 1;
			return ;
		}
		usleep(50);
	}
}
