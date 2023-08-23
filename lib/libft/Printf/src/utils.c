/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:22:36 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/13 15:27:03 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

unsigned int	ft_strlen(const char *str)
{
	int	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	is_in_set(const char c, const char *set)
{
	while (*set && *set != c)
		set++;
	return (*set == c);
}

int	printf_min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

int	printf_max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}
