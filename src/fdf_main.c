/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:31:03 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/24 15:57:19 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int32_t	main(int ac, char **av)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	map_t		*map;
	ft_hook_t	*hook;
	uint32_t	distance;

	map = parse_input(ac, av);
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		handle_error(mlx_strerror(mlx_errno));
	image = mlx_new_image(mlx, mlx->width, mlx->height);
	distance = ft_min(image->width, image->height) / ft_max(map->cols, map->rows);
	if (!image)
	{
		mlx_close_window(mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	draw_image(image, map);
	if (mlx_image_to_window(mlx, image, WIDTH / 2  - (map->cols * distance) / 2, HEIGHT / 2 - (map->rows * distance) / 2))
	{
		mlx_close_window(mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	hook = malloc(sizeof(ft_hook_t));
	hook->mlx = mlx;
	hook->map = map;
	hook->image = image;
	mlx_loop_hook(mlx, ft_hook, hook);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
