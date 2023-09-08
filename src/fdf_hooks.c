/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:56:53 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/02 15:37:43 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	zoom(map_t	*map, mlx_image_t *image, double zoom)
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
	iso_project(map);
	draw_image(image, map);
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
	{
		map->x_offset += 5;
		iso_project(map);
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		map->x_offset -= 5;
		iso_project(map);
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		map->y_offset -= 5;
		iso_project(map);
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		map->y_offset += 5;
		iso_project(map);
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_EQUAL))
		zoom(map, image, 1.02);
	if (mlx_is_key_down(mlx, MLX_KEY_MINUS))
		zoom(map, image, 0.98);
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
	if (mlx_is_key_down(mlx, MLX_KEY_C))
	{
		map->use_zcolor = !(map->use_zcolor);
		iso_project(map);
		draw_image(image, map);
	}
}