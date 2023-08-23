/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:07:52 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/13 15:28:26 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

int	ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}
