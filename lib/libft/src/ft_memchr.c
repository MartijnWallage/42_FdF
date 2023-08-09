/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:38:46 by mwallage          #+#    #+#             */
/*   Updated: 2023/06/01 16:48:49 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*t;
	unsigned char	uc;

	t = (unsigned char *) s;
	uc = (unsigned char) c;
	while (n--)
	{
		if (*t == uc)
			return ((char *) t);
		t++;
	}
	return (NULL);
}
