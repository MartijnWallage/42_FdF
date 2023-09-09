/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:38:25 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/09 17:34:24 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	draw_grid(mlx_image_t *image, map_t *map)
{
 	point2d_t	**points;
	int	i;
	int	j;
 	uint32_t x;
	uint32_t y;

	points = map->map2d;
 	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			x = (points[i][j].x);
			y = (points[i][j].y);
			if (x < image->width && y < image->height)
				mlx_put_pixel(image, x, y, points[i][j].rgba);
		}
	}
}

void	bresenham(mlx_image_t *image, point2d_t a, point2d_t b)
{
    int dx;
    int dy;
    int error[2];
	point2d_t	current;

	current.x = a.x;
	current.y = a.y;
	current.rgba = a.rgba;	
	dx = abs(b.x - a.x);
	dy = abs(b.y - a.y);
	error[0] = dx - dy;
    while (current.x != b.x || current.y != b.y)
	{
		if ((uint32_t)(current.x) < image->width && (uint32_t)(current.y) < image->height)
			mlx_put_pixel(image, current.x, current.y, get_color(current, a, b, dx, dy));
		error[1] = 2 * error[0];
        if (error[1] > -dy)
		{
            error[0] -= dy;
			current.x += (a.x < b.x);
			current.x -= (b.x < a.x);
        }
        if (error[1] < dx)
		{
            error[0] += dx;
			current.y += (a.y < b.y);
			current.y -= (b.y < a.y);
        }
	}
}

void	draw_lines(mlx_image_t *image, map_t *map)
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			if (i + 1 < map->rows)
			{
				if (i == 0 && j == 0)
					project(map, i, j);
				project(map, i + 1, j);
				bresenham(image, map->map2d[i][j], map->map2d[i + 1][j]);
			}
			if (j + 1 < map->cols)
			{
				if (i == 0)
					project(map, i, j + 1);
				bresenham(image, map->map2d[i][j], map->map2d[i][j + 1]);
			}
		}
	}
}

void	draw_reset(mlx_image_t *image)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < image->height)
	{
		j = 0;
		while (j < image->width)
		{
			mlx_put_pixel(image, j, i, BACKGROUND);
			j++;
		}
		i++;
	}
}

void	draw_image(mlx_image_t *image, map_t *map)
{
	draw_reset(image);
	draw_lines(image, map);
//	draw_grid(image, map);
}