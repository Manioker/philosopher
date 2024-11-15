/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:55:54 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/15 14:54:22 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_thread(t_gen *gen)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	pthread_create(&gen->god, NULL, &death_god, &gen->philos[i]);
	while (i < gen->philo_stats.nbr_of_philos)
	{
		pthread_create(&gen->philos[i].thread, NULL, &routine, &gen->philos[i]);
		i++;
	}
	while (j < gen->philo_stats.nbr_of_philos)
	{
		pthread_join(gen->philos[j].thread, NULL);
		j++;
	}
	pthread_mutex_lock(&gen->philo_stats.death_note);
	gen->philo_stats.god_died = 1;
	pthread_mutex_unlock(&gen->philo_stats.death_note);
	pthread_join(gen->god, NULL);
}

void	init_mutex(t_gen *gen)
{
	unsigned int	i;

	i = 0;
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
	if (gen->philo_stats.nbr_of_philos > 200)
	{
		printf("Nope...");
		exit(1);
	}
	gen->philo_stats.time_to_die = ft_atoui(av[2]);
	gen->philo_stats.time_to_eat = ft_atoui(av[3]);
	gen->philo_stats.time_to_sleep = ft_atoui(av[4]);
	gen->philo_stats.time_to_think = ft_abs(gen);
	if (av[5])
		gen->philo_stats.cycles = ft_atoui(av[5]);
	else
		gen->philo_stats.cycles = 0;
	gen->philo_stats.died = 0;
	gen->philo_stats.god_died = 0;
	gen->philo_stats.time_start = ft_get_time();
	pthread_mutex_init(&gen->philo_stats.death_note, NULL);
}

void	destroy_mutex(t_gen *gen)
{
	unsigned int	i;

	i = 0;
	while (i < gen->philo_stats.nbr_of_philos)
	{
		pthread_mutex_destroy(&gen->philos[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&gen->philo_stats.death_note);
}

int	main(int ac, char **av)
{
	t_gen	*gen;

	if (!parsing(ac, av))
	{
		printf("ERROR\n");
		return (1);
	}
	gen = malloc(sizeof(t_gen));
	set_stats(av, gen);
	init_mutex(gen);
	init_thread(gen);
	destroy_mutex(gen);
	return (0);
}
