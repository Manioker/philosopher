/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:57:43 by anvacca           #+#    #+#             */
/*   Updated: 2024/11/15 13:35:31 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

unsigned int	ft_abs(t_gen *gen)
{
	if (gen->philo_stats.time_to_sleep > gen->philo_stats.time_to_eat)
		return (gen->philo_stats.time_to_sleep - gen->philo_stats.time_to_eat);
	else if (gen->philo_stats.time_to_sleep < gen->philo_stats.time_to_eat)
		return (gen->philo_stats.time_to_eat - gen->philo_stats.time_to_sleep);
	return (0);
}
