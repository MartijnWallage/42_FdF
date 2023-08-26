/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:38:25 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/26 17:02:37 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	draw_grid(mlx_image_t *image, map_t *map)
{
	point2d_t	**points;
	int	i;
	int	j;

	points = map->map2d;
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			if (points[i][j].x >= 0 && points[i][j].x < HEIGHT && points[i][j].y >= 0 && points[i][j].y < WIDTH)
				mlx_put_pixel(image, points[i][j].y, points[i][j].x, points[i][j].rgba);
		}
	}
}

void	bresenham(mlx_image_t *image, point2d_t a, point2d_t b)
{
    int dx = abs(b.x - a.x);
    int dy = abs(b.y - a.y);
    int sx = (a.x < b.x) ? 1 : -1;
    int sy = (a.y < b.y) ? 1 : -1;

    int error = dx - dy;

    while (1) {
        // Draw pixel at (x1, y1)
		mlx_put_pixel(image, a.y, a.x, a.rgba);

        if (a.x == b.x && a.y == b.y) {
            break;
        }

        int error2 = 2 * error;

        if (error2 > -dy) {
            error -= dy;
            a.x += sx;
        }

        if (error2 < dx) {
            error += dx;
            a.y += sy;
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
	draw_lines(image, map);
	draw_grid(image, map);
}