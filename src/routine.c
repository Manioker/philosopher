/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:46:08 by anvacca           #+#    #+#             */
/*   Updated: 2024/09/26 12:59:35 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	ft_eat(t_philos *philo)
{
	if (philo->ate)
		return ;
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	printf("current time %lu || philo %u has taken a fork\n", ft_get_time()
		- philo->stats->time_start, philo->id);
	printf("current time %lu || philo %u has taken a fork\n", ft_get_time()
		- philo->stats->time_start, philo->id);
	printf("current time %lu || philo %u is eating\n", ft_get_time()
		- philo->stats->time_start, philo->id);
	ft_usleep(philo->stats->time_to_eat);
	philo->ate = 1;
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	*ft_death(void *args)
{
	t_philos	*philo;

	philo = (t_philos *)args;
	while (1)
	{
		if (ft_get_time() - philo->death >= philo->stats->time_to_die)
		{
			printf("current time %lu || philo %u died\n", ft_get_time()
			- philo->stats->time_start, philo->id);
			exit(1);
		}
	}
	return (NULL);
}

void	ft_sleep(t_philos *philo)
{
	printf("current time %lu || philo %u is sleeping \n", ft_get_time()
		- philo->stats->time_start, philo->id);
	philo->death = ft_get_time();
	ft_usleep(philo->stats->time_to_sleep);
	philo->ate = 0;
}

void	*routine(void *args)
{
	t_philos	*philo;

	philo = (t_philos *)args;
	philo->ate = 0;
	while (1)
		if (philo->stats->key)
			break ;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		printf("current time %lu || philo %u is thinking \n", ft_get_time()
			- philo->stats->time_start, philo->id);
	}
	return (NULL);
}
