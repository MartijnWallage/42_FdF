/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:59:34 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/25 13:38:12 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static point2d_t	**iso(map_t *map)
{
    point2d_t   **projection;
    point3d_t   **source;
    int         i;
    int         j;
    
    source = map->map3d;
    projection = malloc(sizeof(point2d_t *) * map->rows);
    // protect malloc
    i = -1;
    while (++i < map->rows)
    {
        projection[i] = malloc(sizeof(point2d_t) * map->cols);
        // protect malloc
        j = -1;
        while (++j < map->cols)
        {
            projection[i][j].x = source[i][j].x
                + cos(0.46373398) * source[i][j].z
                - cos(0.46373398) * (source[i][j].y);
            projection[i][j].y = -(source[i][j].y) * sin(0.46373398)
                - source[i][j].z * sin(0.46373398);
            projection[i][j].x += WIDTH / 2;
            projection[i][j].y += HEIGHT / 2;
            projection[i][j].rgba = (map->map3d)[i][j].rgba;
        }
    }
    return (projection);
}

void	iso_project(map_t *map)
{
    map->map2d = iso(map);
}
