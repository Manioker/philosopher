/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:46:08 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/14 15:13:40 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_eat(t_philos *philo)
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
	{
		printf("%lu %u has taken a fork\n", ft_get_time()
			- philo->stats->time_start, philo->id);
		printf("%lu %u has taken a fork\n", ft_get_time()
			- philo->stats->time_start, philo->id);
		printf("%lu %u is eating\n", ft_get_time() - philo->stats->time_start,
			philo->id);
	}
	pthread_mutex_unlock(&philo->stats->death_note);
	philo->death_timer = ft_get_time();
	ft_wait(philo->stats->time_to_eat, philo);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	ft_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->stats->death_note);
	if (philo->stats->died == 0 && philo->is_dead == 0)
		printf("%lu %u is sleeping\n", ft_get_time() - philo->stats->time_start,
			philo->id);
	pthread_mutex_unlock(&philo->stats->death_note);
	if (philo->is_dead == 1)
		return ;
	ft_wait(philo->stats->time_to_sleep, philo);
}

static void	ft_think(t_philos *philo)
{
	pthread_mutex_lock(&philo->stats->death_note);
	if (philo->stats->died == 0 && philo->is_dead == 0)
	{
		printf("%lu %u is thinking\n", ft_get_time() - philo->stats->time_start,
			philo->id);
	}
	pthread_mutex_unlock(&philo->stats->death_note);
	ft_wait(ft_abs(philo->stats->time_to_eat - philo->stats->time_to_sleep),
		philo);
}

void	*routine(void *args)
{
	t_philos		*philo;
	unsigned int	cycles;

	philo = (t_philos *)args;
	cycles = philo->stats->cycles;
	if (philo->stats->nbr_of_philos == 1)
		ft_wait(philo->stats->time_to_die, philo);
	if (philo->id % 2 == 0)
		ft_think(philo);
	while (1)
	{
		pthread_mutex_lock(&philo->stats->death_note);
		if ((philo->stats->died == 1) || (philo->stats->cycles > 0 && cycles <= 0))
			break ;
		pthread_mutex_unlock(&philo->stats->death_note);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		cycles--;
	}
	if ((philo->stats->died == 1) || (philo->stats->cycles > 0 && cycles <= 0))
		pthread_mutex_unlock(&philo->stats->death_note);
	return (NULL);
}
