/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:35:18 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/24 14:44:10 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	handle_error(const char *message)
{
	ft_putendl_fd((char *)message, 2);
	exit(1);
}

void	error_map(int fd, map_t *map, char *line)
{
	close(fd);
	free(map);
	if (line)
		free(line);
	handle_error("mlx: invalid map.");
}