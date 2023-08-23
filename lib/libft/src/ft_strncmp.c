/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:42:44 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/12 17:50:49 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (*str1 == *str2)
	{
		if (*str1 == '\0')
			return (0);
		++str1;
		++str2;
	}
	return ((int)(*str1 - *str2));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (n > 1 && *str1 == *str2)
	{
		if (*str1 == '\0')
			return (0);
		++str1;
		++str2;
		--n;
	}
	return ((int)(*str1 - *str2));
}
