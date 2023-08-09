/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:14:31 by mwallage          #+#    #+#             */
/*   Updated: 2023/06/01 16:48:10 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	recursion(char *str, unsigned int nb)
{
	if (nb > 9)
		recursion(str, nb / 10);
	while (*str)
		str++;
	*str = nb % 10 + '0';
}

char	*ft_itoa(int n)
{
	char			*result;
	unsigned int	nb;
	unsigned int	div;
	unsigned int	digits;
	unsigned int	neg;

	neg = (n < 0);
	nb = (unsigned int)(n);
	if (neg)
		nb = (unsigned int)(n * -1);
	div = 1;
	digits = 1;
	while (nb / div > 9)
	{
		div *= 10;
		digits++;
	}
	result = malloc(digits + 1 + neg);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, digits + 1 + neg);
	if (neg)
		*result = '-';
	recursion(result, nb);
	return (result);
}
