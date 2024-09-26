/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:46:08 by anvacca           #+#    #+#             */
/*   Updated: 2024/09/26 16:03:03 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_eat(t_philos *philo)
{
	if (philo->ate)
		return ;
	if (philo->stats->died == 1)
		return ;
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	printf("current time %lu || philo %u has taken a fork\n", ft_get_time()
		- philo->stats->time_start, philo->id);
	printf("current time %lu || philo %u has taken a fork\n", ft_get_time()
		- philo->stats->time_start, philo->id);
	printf("current time %lu || philo %u is eating\n", ft_get_time()
		- philo->stats->time_start, philo->id);
	philo->death_timer = ft_get_time();
	ft_wait(philo->stats->time_to_eat, philo);
	if (philo->stats->died == 1)
		return ;
	philo->ate = 1;
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	ft_sleep(t_philos *philo)
{
	printf("current time %lu || philo %u is sleeping \n", ft_get_time()
		- philo->stats->time_start, philo->id);
	ft_wait(philo->stats->time_to_sleep, philo);
	if (philo->stats->died == 1)
		return ;
	philo->ate = 0;
}

void	*routine(void *args)
{
	t_philos	*philo;

	philo = (t_philos *)args;
	philo->ate = 0;
	if (philo->stats->nbr_of_philos == 1)
		ft_wait(philo->stats->time_to_die, philo);
	while (1)
		if (philo->stats->key)
			break ;
	if (philo->id % 2 == 0)
		usleep(100);
	while (philo->stats->died == 0)
	{
		philo->death_timer = ft_get_time();
		ft_eat(philo);
		if (philo->stats->died)
			break ;
		ft_sleep(philo);
		if (philo->stats->died)
			break ;
		printf("current time %lu || philo %u is thinking \n", ft_get_time()
			- philo->stats->time_start, philo->id);
	}
	return (NULL);
}
