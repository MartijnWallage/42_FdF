/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:38:25 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/07 18:36:48 by mwallage         ###   ########.fr       */
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


int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

/*
** Get color. Result depends on point position.
** This function is needed to create linear gradient.
*/

int	get_color(point2d_t current, point2d_t a, point2d_t b, int dx, int dy)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (current.rgba == b.rgba)
		return (current.rgba);
	if (dx > dy)
		percentage = percent(a.x, b.x, current.x);
	else
		percentage = percent(a.y, b.y, current.y);
	red = get_light(get_r(a.rgba), get_r(b.rgba), percentage);
	green = get_light(get_g(a.rgba), get_g(b.rgba), percentage);
	blue = get_light(get_b(a.rgba), get_b(b.rgba), percentage);
	return ((red << 24) | (green << 16) | blue << 8 | 0xFF);
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
				bresenham(image, map->map2d[i][j], map->map2d[i + 1][j]);
			if (j + 1 < map->cols)
				bresenham(image, map->map2d[i][j], map->map2d[i][j + 1]);
		}
	}
}

void	draw_image(mlx_image_t *image, map_t *map)
{
	draw_reset(image);
	draw_lines(image, map);
//	draw_grid(image, map);
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