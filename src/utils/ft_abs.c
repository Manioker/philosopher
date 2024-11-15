/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:57:43 by anvacca           #+#    #+#             */
/*   Updated: 2024/10/22 16:07:32 by anvacca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

unsigned int	ft_abs(unsigned int nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	return (nbr);
}
