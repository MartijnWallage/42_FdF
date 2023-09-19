/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:56:53 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/19 16:31:29 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	zoom(fdf_t *fdf, double zoom)
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < fdf->map->rows)
	{
		j = -1;
		while (++j < fdf->map->cols)
		{
			fdf->map->map3d[i][j].x *= zoom;
			fdf->map->map3d[i][j].y *= zoom;
			fdf->map->map3d[i][j].z *= zoom;
		}
	}
	draw_image(fdf);
}

void fdf_scrollhook(double xdelta, double ydelta, void* param)
{
	fdf_t	*hook;
	map_t		*map;
	mlx_image_t	*image;

	hook = (fdf_t *)param;
	map = hook->map;
	image = hook->image;
	if (ydelta > 0)
		zoom(hook, 1.02);
	else if (ydelta < 0)
		zoom(hook, 0.98);
	xdelta++;
}

void ft_hook(void* param)
{
	fdf_t	*hook;
	mlx_t		*mlx;
	mlx_image_t	*image;
	map_t		*map;
	
	hook = (fdf_t *)param;
	mlx = hook->mlx;
	image = hook->image;
	map = hook->map;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		map->x_offset -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		map->x_offset += 5; 
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		map->y_offset += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		map->y_offset -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_EQUAL))
		zoom(hook, 1.02);
	if (mlx_is_key_down(mlx, MLX_KEY_MINUS))
		zoom(hook, 0.98);
	draw_image(hook);
}

void ft_hook_project(void *param)
{
	fdf_t	*fdf;
	mlx_t	*mlx;
	map_t	*map;

	fdf = (fdf_t *)param;
	mlx = fdf->mlx;
	map = fdf->map;
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		map->alpha += 0.05; 
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		map->beta += 0.05;
	if (mlx_is_key_down(mlx, MLX_KEY_C))
		map->use_zcolor = !(map->use_zcolor);
	if (mlx_is_key_down(mlx, MLX_KEY_1))
	{
		map->alpha = 0.523599;
		map->beta = map->alpha;
	}		
	if (mlx_is_key_down(mlx, MLX_KEY_2))
	{
		map->alpha = 0.6370452;
		map->beta = map->alpha;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_3))
	{
		map->alpha = 0.46373398 / 2;;
		map->beta = 0.46373398;
	}
	draw_image(fdf);
}

void ft_hook_rotate(void *param)
{
	fdf_t	*fdf;

	fdf = (fdf_t *) param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_X) && mlx_is_key_down(fdf->mlx, MLX_KEY_COMMA))
		rotate_all(fdf->map, 'x', -0.02);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_X) && mlx_is_key_down(fdf->mlx, MLX_KEY_PERIOD))
		rotate_all(fdf->map, 'x', 0.02);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Y) && mlx_is_key_down(fdf->mlx, MLX_KEY_COMMA))
		rotate_all(fdf->map, 'y', -0.02);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Y) && mlx_is_key_down(fdf->mlx, MLX_KEY_PERIOD))
		rotate_all(fdf->map, 'y', 0.02);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z) && mlx_is_key_down(fdf->mlx, MLX_KEY_COMMA))
		rotate_all(fdf->map, 'z', -0.02);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z) && mlx_is_key_down(fdf->mlx, MLX_KEY_PERIOD))
		rotate_all(fdf->map, 'z', 0.02);
	draw_image(fdf);
}