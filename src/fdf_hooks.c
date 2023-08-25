/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:56:53 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/25 12:12:11 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void ft_hook(void* param)
{
	ft_hook_t	*hook;
	mlx_t		*mlx;
	mlx_image_t	*image;
	
	hook = (ft_hook_t *)param;
	mlx = (mlx_t *)(hook->mlx);
	image = (mlx_image_t *)(hook->image);
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
}