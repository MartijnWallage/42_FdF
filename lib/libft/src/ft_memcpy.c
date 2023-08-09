/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:03:15 by mwallage          #+#    #+#             */
/*   Updated: 2023/06/01 16:49:14 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*str_dest;
	unsigned char	*str_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	str_dest = (unsigned char *) dest;
	str_src = (unsigned char *) src;
	while (n-- > 0)
		*str_dest++ = *str_src++;
	return (dest);
}
