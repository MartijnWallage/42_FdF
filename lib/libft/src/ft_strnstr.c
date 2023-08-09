/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:07:26 by mwallage          #+#    #+#             */
/*   Updated: 2023/06/01 16:51:55 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	match(const char *big, const char *little, size_t len)
{
	while (len && *big == *little)
	{
		if (*big == '\0')
			return (1);
		big++;
		little++;
		len--;
	}
	return (*little == '\0');
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	if (*little == 0)
		return ((char *) big);
	while (len && *big)
	{
		if (match(big, little, len))
			return ((char *) big);
		big++;
		len--;
	}
	return (NULL);
}
