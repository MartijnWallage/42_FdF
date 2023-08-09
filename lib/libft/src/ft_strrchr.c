/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:20:28 by mwallage          #+#    #+#             */
/*   Updated: 2023/06/01 16:52:02 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*t;

	t = NULL;
	while (*s != '\0')
	{
		if (*s == (unsigned char) c)
			t = s;
		s++;
	}
	if ((unsigned char) c == '\0')
		t = s;
	return ((char *) t);
}
