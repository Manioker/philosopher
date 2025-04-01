/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_think.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:25:55 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/22 11:22:22 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_think(t_philos *philo)
{
	if (philo->stats->died == 0)
	{
		printf("%lu %u is thinking\n", ft_get_time() - philo->stats->time_start,
			philo->id);
	}
}
