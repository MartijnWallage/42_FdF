/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:56:53 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/12 19:28:36 by mwallage         ###   ########.fr       */
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
		map->x_offset -= 5;
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		map->x_offset += 5;
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		map->y_offset += 5;
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		map->y_offset -= 5;
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_EQUAL))
		zoom(map, image, 1.02);
	if (mlx_is_key_down(mlx, MLX_KEY_MINUS))
		zoom(map, image, 0.98);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		map->alpha += 0.05;
		draw_image(image, map); 
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		map->beta += 0.05;
		draw_image(image, map); 
	}
	if (mlx_is_key_down(mlx, MLX_KEY_C))
	{
		map->use_zcolor = !(map->use_zcolor);
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_1))
	{
		map->alpha = 0.523599;
		map->beta = map->alpha;
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_2))
	{
		map->alpha = 0.6370452;
		map->beta = map->alpha;
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_3))
	{
		map->alpha = 0.46373398 / 2;;
		map->beta = 0.46373398;
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_X) && mlx_is_key_down(mlx, MLX_KEY_COMMA))
	{
		rotate_all(map, 'x', -0.02);
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_X) && mlx_is_key_down(mlx, MLX_KEY_PERIOD))
	{
		rotate_all(map, 'x', 0.02);
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_Y) && mlx_is_key_down(mlx, MLX_KEY_COMMA))
	{
		rotate_all(map, 'y', -0.02);
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_Y) && mlx_is_key_down(mlx, MLX_KEY_PERIOD))
	{
		rotate_all(map, 'y', 0.02);
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_Z) && mlx_is_key_down(mlx, MLX_KEY_COMMA))
	{
		rotate_all(map, 'z', -0.02);
		draw_image(image, map);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_Z) && mlx_is_key_down(mlx, MLX_KEY_PERIOD))
	{
		rotate_all(map, 'z', 0.02);
		draw_image(image, map);
	}
}