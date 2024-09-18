/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:00:07 by anvacca           #+#    #+#             */
/*   Updated: 2024/09/18 15:07:00 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static t_bool	isnumber(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

t_bool	check_argv(char **av)
{
	unsigned int	i;

	i = 0;
	while (av[i])
	{
		if (!isnumber(av[i]))
		{
			printf("Incorect Arguments!\n");
			return (false);
		}
		i++;
	}
	if ((av[4] && av[4][0] == '0') || !av[i - 1][0])
	{
		printf("┌П┐(◉_◉)┌П┐\n");
		exit(1);
	}
	return (true);
}

t_bool	check_argc(int ac)
{
	if (ac != 5 && ac != 6)
	{
		if (ac == 1)
			printf("Missing number of philosophers!\n");
		if (ac == 2)
			printf("Missing time to die!\n");
		if (ac == 3)
			printf("Missing time to eat!\n");
		if (ac == 4)
			printf("Missing time to sleep!\n");
		if (ac >= 7)
			printf("Too many arguments!\n");
		return (false);
	}
	return (true);
}
