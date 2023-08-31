/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:56:53 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/31 14:22:58 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	zoom(map_t	*map, double zoom)
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < map->rows)
	{
		j = -1;
		while (++j < map->cols)
		{
			map->map3d[i][j].x *= zoom;
			map->map3d[i][j].y *= zoom;
			map->map3d[i][j].z *= zoom;
		}
	}
}

void ft_hook(void* param)
{
	ft_hook_t	*hook;
	mlx_t		*mlx;
	mlx_image_t	*image;
	map_t		*map;
	
	hook = (ft_hook_t *)param;
	mlx = (mlx_t *)(hook->mlx);
	image = (mlx_image_t *)(hook->image);
	map = (map_t *)(hook->map);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances->x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances->x += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances->y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances->y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_EQUAL))
	{
		zoom(map, 1.02);
		iso_project(map);
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_MINUS))
	{
		zoom(map, 0.98);
		iso_project(map);
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_R))
	{
		map->alpha += 0.05;
		iso_project(map);
		draw_image(image, map); 
	}
	if (mlx_is_key_down(mlx, MLX_KEY_T))
	{
		map->beta += 0.05;
		iso_project(map);
		draw_image(image, map); 
	}
}