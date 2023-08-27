/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:38:25 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/26 18:20:36 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	draw_grid(mlx_image_t *image, map_t *map)
{
 	point2d_t	**points;
	int	i;
	int	j;
 	int x;
	int y;

	points = map->map2d;
 	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			x = (points[i][j].x);
			y = (points[i][j].y);
			if (x > 0 && y > 0)
				mlx_put_pixel(image, x, y, 0xFF0000FF);
		}
	}
}


/* int	ft_abs(float a, float b)
{
	float	temp;

	temp = a - b;
	if (temp >= 0)
		return ((int)temp);
	else
		return ((int)-temp);	
}
 */
void	bresenham(mlx_image_t *image, point2d_t a, point2d_t b)
{
    int dx = abs(b.y - a.y);
    int dy = abs(b.x - a.x);
    int sx = (a.y < b.y) ? 1 : -1;
    int sy = (a.x < b.x) ? 1 : -1;

    int error = dx - dy;

    while (1) 
	{
		mlx_put_pixel(image, a.x, a.y, a.rgba);

        if (a.y == b.y && a.x == b.x) {
            break;
        }

        int error2 = 2 * error;

        if (error2 > -dy) {
            error -= dy;
            a.y += sx;
        }

        if (error2 < dx) {
            error += dx;
            a.x += sy;
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
	int32_t	i;
	int32_t	j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			mlx_put_pixel(image, j, i, 0x000000);
		}
	}
}