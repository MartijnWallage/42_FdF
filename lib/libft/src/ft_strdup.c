/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:43:11 by mwallage          #+#    #+#             */
/*   Updated: 2023/06/01 16:50:52 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		size;

	size = 0;
	while (s[size])
		size++;
	size++;
	copy = (char *) malloc(size * sizeof(char));
	if (copy == NULL)
		return (NULL);
	while (size--)
		copy[size] = s[size];
	return (copy);
}
