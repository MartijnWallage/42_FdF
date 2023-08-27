/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:59:34 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/26 17:30:45 by mwallage         ###   ########.fr       */
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
/*              projection[i][j].y = source[i][j].y + cos(0.46373398) * source[i][j].z
                - cos(0.46373398) * (source[i][j].x);
            projection[i][j].x = source[i][j].x * sin(0.46373398) - source[i][j].z * sin(0.26373398); */
            projection[i][j].y = (int) (source[i][j].y * cos(0.46373398) - source[i][j].x * sin(0.46373398) + WIDTH / 3);
            projection[i][j].x = (int) (source[i][j].y * sin(0.46373398) + source[i][j].x * cos(0.46373398) - source[i][j].z * sin(0.23186699) + HEIGHT / 3);
            projection[i][j].rgba = source[i][j].rgba;
        }
    }
    return (projection);
}

void	iso_project(map_t *map)
{
    map->map2d = iso(map);
}
