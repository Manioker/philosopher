/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:25:58 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/15 13:34:14 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	help_to_eat(t_philos *philo)
{
	printf("%lu %u has taken a fork\n", ft_get_time()
		- philo->stats->time_start, philo->id);
	printf("%lu %u has taken a fork\n", ft_get_time()
		- philo->stats->time_start, philo->id);
	printf("%lu %u is eating\n", ft_get_time() - philo->stats->time_start,
		philo->id);
}

void	ft_eat(t_philos *philo)
{
	if (&philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
	}
	pthread_mutex_lock(&philo->stats->death_note);
	if (philo->stats->died == 0 && philo->is_dead == 0)
		help_to_eat(philo);
	pthread_mutex_unlock(&philo->stats->death_note);
	philo->death_timer = ft_get_time();
	ft_wait(philo->stats->time_to_eat, philo);
	pthread_mutex_lock(&philo->stats->death_note);
	philo->stats->ate = 1;
	pthread_mutex_unlock(&philo->stats->death_note);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
