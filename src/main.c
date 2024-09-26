/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:55:54 by anvacca           #+#    #+#             */
/*   Updated: 2024/09/25 16:07:16 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_thread(t_gen *gen)
{
	unsigned int	i;

	i = 0;
	while (i < gen->philo_stats.nbr_of_philos)
	{
		pthread_create(&gen->philos[i].thread, NULL, &routine, &gen->philos[i]);
		i++;
	}
	gen->philo_stats.key = 1;
	i = 0;
	while (i < gen->philo_stats.nbr_of_philos)
	{
		pthread_join(gen->philos[i].thread, NULL);
		i++;
	}
}

void	init_mutex(t_gen *gen)
{
	unsigned int	i;

	i = 0;
	gen->philos = malloc(sizeof(t_philos) * gen->philo_stats.nbr_of_philos);
	while (i < gen->philo_stats.nbr_of_philos)
	{
		gen->philos[i].id = i + 1;
		gen->philos[i].stats = &gen->philo_stats;
		pthread_mutex_init(&gen->philos[i].left_fork, NULL);
		if (i == gen->philo_stats.nbr_of_philos - 1)
			gen->philos[i].right_fork = &gen->philos[0].left_fork;
		else
			gen->philos[i].right_fork = &gen->philos[i + 1].left_fork;
		i++;
	}
}

void	set_stats(char **av, t_gen *gen)
{
	gen->philo_stats.nbr_of_philos = ft_atoui(av[1]);
	gen->philo_stats.time_to_die = ft_atoui(av[2]);
	gen->philo_stats.time_to_eat = ft_atoui(av[3]);
	gen->philo_stats.time_to_sleep = ft_atoui(av[4]);
	if (av[5])
		gen->philo_stats.cycles = ft_atoui(av[5]);
	else
		gen->philo_stats.cycles = 0;
	gen->philo_stats.key = 0;
	gen->philo_stats.time_start = ft_get_time();
}

int	main(int ac, char **av)
{
	t_gen	*gen;

	if (!parsing(ac, av))
	{
		printf("ERROR\nUsage:<number_of_philo> <time_to_die> <time_to_eat> <time_to_sleep>\n");
		exit(1);
	}
	gen = malloc(sizeof(t_gen));
	set_stats(av, gen);
	init_mutex(gen);
	init_thread(gen);
	free(gen);
	return (0);
}
