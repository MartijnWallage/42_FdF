/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:59:34 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/09 16:47:38 by mwallage         ###   ########.fr       */
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
    if (!projection)
    {
        free(map);
        handle_error("malloc failed");
    }
    i = -1;
    while (++i < map->rows)
    {
        projection[i] = malloc(sizeof(point2d_t) * map->cols);
        if (!projection[i])
        {
            ft_free_tab((void **)projection);
            handle_error("malloc failed");
        }
        j = -1;
        while (++j < map->cols)
        {
            // 2:1 dimetric:
/*             projection[i][j].x = (int)(source[i][j].x * cos(map->alpha)
                - source[i][j].y * sin(map->alpha))
                + WIDTH / 2
                + map->x_offset;
            projection[i][j].y = (int)(source[i][j].x * sin(map->alpha)
                + source[i][j].y * cos(map->alpha)
                - source[i][j].z * sin(map->beta))
                + HEIGHT / 2
                + map->y_offset; */
            // true isometric?
            projection[i][j].x = (source[i][j].x - source[i][j].y) * cos(map->beta)
                + WIDTH / 2
                + map->x_offset;
            projection[i][j].y = -(source[i][j].z) + (source[i][j].x + source[i][j].y) * sin(map->alpha)
                + HEIGHT / 2
                + map->y_offset;
            // parallel:
/*             projection[i][j].x = source[i][j].x - source[i][j].z * cos(map->alpha)
                + WIDTH / 2
                + map->x_offset;
            projection[i][j].y = source[i][j].y - source[i][j].z * sin(map->alpha)
                + HEIGHT / 2
                + map->y_offset; */
            if (map->use_zcolor)
                projection[i][j].rgba = source[i][j].zcolor;
            else
                projection[i][j].rgba = source[i][j].mapcolor;
        }
    }
    return (projection);
}

void	iso_project(map_t *map)
{
    map->map2d = iso(map);
}

/* void    project(point3d_t *previous, point2d_t *new)
{
    if (map->)
    new->x = 
} */