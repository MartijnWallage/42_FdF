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
			if (x >= 0 && x < image->width && y >= 0 && y < image->height)
				mlx_put_pixel(image, x, y, points[i][j].rgba);
		}
	}
}


/* unsigned int	get_color(int dx, int dy, point2d_t a, point2d_t b, unsigned int a_color, unsigned int b_color)
{
	float	ax;
	float	ay;
	unsigned int	blue;
	unsigned int	red;
	unsigned int	green;
		
	if (a_color == b_color)
		return (a_color);
	ax = abs(b.x - a.x) / dx;
	ay = abs(b.y - a.y) / dy;
	//	THe basic idea is: say there are ten steps from a to b. Then each step, the color in each channel should be increased or descreased 1/10th. 
} */

void	bresenham(mlx_image_t *image, point2d_t a, point2d_t b)
{
    int dx;
    int dy;
    int error;
	int	error2;/* 
	int	blue_inc;
	int	green_inc;
	int	red_inc; */

	dx = abs(b.x - a.x);
	dy = abs(b.y - a.y);
	error = dx - dy;/* 
	if (ft_max(dx, dy) == 0)
	{
		blue_inc = 0;
		green_inc = 0;
		red_inc = 0;
	}
	else
	{
		blue_inc = ((get_b(b.rgba) - get_b(a.rgba)) / ft_max(dx, dy));
		green_inc = ((get_g(b.rgba) - get_g(a.rgba)) / ft_max(dx, dy));
		red_inc = ((get_r(b.rgba) - get_r(a.rgba)) / ft_max(dx, dy));
	} */
    while (a.y != b.y || a.x != b.x)
	{
		if ((uint32_t)(a.x) < image->width && (uint32_t)(a.y) < image->height)
			mlx_put_pixel(image, a.x, a.y, a.rgba);
		error2 = 2 * error;
        if (error2 > -dy)
		{
            error -= dy;
			a.x += (a.x < b.x);
			a.x -= (b.x < a.x);
        }
        if (error2 < dx)
		{
            error += dx;
			a.y += (a.y < b.y);
			a.y -= (b.y < a.y);
        }
		a.rgba = get_rgba(get_r(a.rgba) + 1, get_g(a.rgba) + 1, get_b(a.rgba) + 1, 0xFF);
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