/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:38:25 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/24 15:56:32 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	draw_grid(mlx_image_t *image, map_t *map)
{
	point3d_t	*points;

	points = (map->map2d) - 1;
	while (++points)
		mlx_put_pixel(image, points->x, points->y, points->rgba);
}

void	draw_lines(mlx_image_t *image, map_t *map)
{
	uint32_t	i;
	uint32_t	j;
	
	i = -1;
	while (++i <= (map->rows - 1) * (map->interval))
	{
		j = -1;
		while (++j <= (map->cols - 1) * (map->interval))
		{
			if (i % map->interval == 0 || j % map->interval == 0)
				mlx_put_pixel(image, j, i, 0xEEDDFFFF);
		}
	}	
}

void	draw_image(mlx_image_t *image, map_t *map)
{
	draw_grid(image, map);
	draw_lines(image, map);
}