/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:56:53 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/09 17:57:48 by mwallage         ###   ########.fr       */
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
	draw_image(image, map);
}

void my_scrollhook(double xdelta, double ydelta, void* param)
{
	ft_hook_t	*hook;
	map_t		*map;
	mlx_image_t	*image;

	hook = (ft_hook_t *)param;
	map = hook->map;
	image = hook->image;
	if (ydelta > 0)
		zoom(map, image, 1.02);
	else if (ydelta < 0)
		zoom(map, image, 0.98);
	xdelta++;
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
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		map->x_offset -= 5;
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		map->y_offset -= 5;
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		map->y_offset += 5;
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_EQUAL))
		zoom(map, image, 1.02);
	if (mlx_is_key_down(mlx, MLX_KEY_MINUS))
		zoom(map, image, 0.98);
	if (mlx_is_key_down(mlx, MLX_KEY_R))
	{
		map->alpha += 0.05;
		draw_image(image, map); 
	}
	if (mlx_is_key_down(mlx, MLX_KEY_T))
	{
		map->beta += 0.05;
		draw_image(image, map); 
	}
	if (mlx_is_key_down(mlx, MLX_KEY_C))
	{
		map->use_zcolor = !(map->use_zcolor);
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_I))
	{
		map->projection = 'i';
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_P))
	{
		map->projection = 'p';
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		map->projection = 'd';
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_X))
	{
		map->rotate_x += 0.01;
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_Y))
	{
		map->rotate_y += 0.01;
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_Z))
	{
		map->rotate_z += 0.01;
		draw_image(image, map);
	}
}