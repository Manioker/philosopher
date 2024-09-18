/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:55:54 by anvacca           #+#    #+#             */
/*   Updated: 2024/09/18 14:26:29 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void set_stats(int ac, char **av, t_philo	*philo_stats)
{
	philo_stats->stats.nbr_of_philos = ft_atoui(av[1]);
	philo_stats->stats.time_to_die = ft_atoui(av[2]);
	philo_stats->stats.time_to_eat = ft_atoui(av[3]);
	philo_stats->stats.time_to_sleep = ft_atoui(av[4]);
	if (ac == 6)
		philo_stats->stats.cycles = ft_atoui(av[5]);
	else
		philo_stats->stats.cycles = -1;
}

int	main(int ac, char **av)
{
	t_philo	*philo_stats;

	if (!check_argv(av + 1) || !check_argc(ac))
	{
		printf("Usage: <time_to_die> <time_to_eat> <time_to_sleep>\n");
		exit(1);
	}
	philo_stats = malloc(sizeof(t_philo));
	set_stats(ac, av, philo_stats);
	free(philo_stats);
	return (0);
}
