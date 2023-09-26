/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:56:53 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/26 18:02:40 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	zoom(t_fdf *fdf, double zoom)
{
	if (fdf->map->zoom * zoom > 0 && fdf->map->zoom < DBL_MAX / zoom)
		fdf->map->zoom *= zoom;
}

void	fdf_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fdf		*fdf;

	fdf = (t_fdf *)param;
	if (ydelta > 0)
		zoom(fdf, 1.02);
	else if (ydelta < 0)
		zoom(fdf, 0.98);
	xdelta++;
}

void	ft_hook(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
		fdf->map->x_offset -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
		fdf->map->x_offset += 5; 
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
		fdf->map->y_offset += 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
		fdf->map->y_offset -= 5;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_EQUAL))
		zoom(fdf, 1.02);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_MINUS))
		zoom(fdf, 0.98);
}

void	ft_hook_project(void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_C))
		fdf->map->use_zcolor = !(fdf->map->use_zcolor);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_1))
	{
		fdf->map->alpha = 0.523599;
		fdf->map->beta = fdf->map->alpha;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_2))
	{
		fdf->map->alpha = 0.6370452;
		fdf->map->beta = fdf->map->alpha;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_3))
	{
		fdf->map->alpha = 0.46373398 / 2;
		fdf->map->beta = 0.46373398;
	}
}

void	ft_hook_rotate(void *param)
{
	t_fdf	*fdf;
	double	sign;

	fdf = (t_fdf *) param;
	sign = 0;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_COMMA))
		sign = -1;
	else if (mlx_is_key_down(fdf->mlx, MLX_KEY_PERIOD))
		sign = 1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->map->alpha += sign * 0.05; 
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->map->beta += sign * 0.05;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_X))
		rotate_all(fdf->map, 'x', sign * 0.02);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Y))
		rotate_all(fdf->map, 'y', sign * 0.02);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Z))
		rotate_all(fdf->map, 'z', sign * 0.02);
}
