/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:25:58 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/22 11:25:26 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	left_fork_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->stats->death_note);
	if (philo->stats->died == 0)
		printf("%lu %u has taken a fork\n", ft_get_time()
			- philo->stats->time_start, philo->id);
	pthread_mutex_unlock(&philo->stats->death_note);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->stats->death_note);
	if (philo->stats->died == 0)
		printf("%lu %u has taken a fork\n", ft_get_time()
			- philo->stats->time_start, philo->id);
	pthread_mutex_unlock(&philo->stats->death_note);
}

static void	right_fork_eat(t_philos *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->stats->death_note);
	if (philo->stats->died == 0)
		printf("%lu %u has taken a fork\n", ft_get_time()
			- philo->stats->time_start, philo->id);
	pthread_mutex_unlock(&philo->stats->death_note);
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->stats->death_note);
	if (philo->stats->died == 0)
		printf("%lu %u has taken a fork\n", ft_get_time()
			- philo->stats->time_start, philo->id);
	pthread_mutex_unlock(&philo->stats->death_note);
}

void	ft_eat(t_philos *philo)
{
	if (&philo->left_fork < philo->right_fork)
		left_fork_eat(philo);
	else
		right_fork_eat(philo);
	pthread_mutex_lock(&philo->stats->death_note);
	if (philo->stats->died == 0)
		printf("%lu %u is eating\n", ft_get_time() - philo->stats->time_start,
			philo->id);
	philo->death_timer = ft_get_time();
	philo->meal++;
	pthread_mutex_unlock(&philo->stats->death_note);
	ft_wait(philo->stats->time_to_eat, philo);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
