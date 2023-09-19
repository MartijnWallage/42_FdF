/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:59:34 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/19 16:44:48 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	project(map_t *map, int i, int j)
{
	point3d_t	*previous;
	point2d_t	*new;

	previous = &(map->map3d[i][j]);
	new = &(map->map2d[i][j]);
	new->x = (int)((previous->x - previous->y)
			* cos(map->alpha)
			+ WIDTH / 2 + map->x_offset);
	new->y = (int)(-previous->z
			+ (previous->x + previous->y) * sin(map->beta)
			+ HEIGHT / 2 + map->y_offset);
	if (map->use_zcolor)
		new->rgba = previous->zcolor;
	else
		new->rgba = previous->mapcolor;
}
