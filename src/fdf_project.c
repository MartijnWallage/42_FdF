/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:59:34 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/07 17:56:41 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int    project_color(map_t *map, int i, int j)
{
    point3d_t   *point;
    int         rgba;

    point = &(map->map3d[i][j]);
    if (!map->z_color || (map->high - map->low) == 0 || (point->z_unparsed - map->low) == 0)
        return (point->rgba);
    rgba = 0xFF;
    if (point->z_unparsed - map->low < (map->high - map->low) / 3)
        rgba += (255 / (map->high - map->low) * (point->z_unparsed - map->low)) << 8;
    else if (point->z_unparsed - map->low < (map->high - map->low) / 2)
        rgba += (255 / (map->high - map->low) * (point->z_unparsed - map->low)) << 16;
    else
        rgba += (255 / (map->high - map->low) * (point->z_unparsed - map->low)) << 24;
    return (rgba);
}

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
            projection[i][j].rgba = project_color(map, i, j);
            projection[i][j].z = source[i][j].z;
        }
    }
    return (projection);
}

void	iso_project(map_t *map)
{
    map->map2d = iso(map);
}
