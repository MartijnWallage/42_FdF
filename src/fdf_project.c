/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:59:34 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/24 15:55:48 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static point2d_t	*iso(map_t *map)
{
    point2d_t   *projection;

    projection = malloc(sizeof(point2d_t) * (map->cols * map->rows + 1));
    if (!projection)
    {
        free(map);
        handle_error("malloc failed");
    }
    projection[map->cols * map->rows] = NULL;
    while (points)
    {
        projection->x = (points->x - points->y) * cos(0.46373398);
        projection->y = -points->z + (points->x + points->y) * sin(0.46373398);
        projection->rgba = points->rgba;
        points++;
        projection++;
    }
}

void	iso_project(map_t *map)
{
    map->projection = iso(map);
}