/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:31:03 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/19 17:05:00 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static fdf_t	*init_fdf(int ac, char **av)
{
	map_t		*map;
	mlx_t		*mlx;
	mlx_image_t	*image;
	fdf_t		*fdf;
	
	map = parse_input(ac, av);
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		handle_error(mlx_strerror(mlx_errno));
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image)
	{
		mlx_close_window(mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	fdf = malloc(sizeof(fdf_t));
	if (!fdf)
		handle_error("malloc failed");
	fdf->image = image;
	fdf->mlx = mlx;
	fdf->map = map;
	return (fdf);
}

int32_t	main(int ac, char **av)
{
	fdf_t		*fdf;

	if (ac != 2)
		handle_error(FORMAT);
	fdf = init_fdf(ac, av);
	display_menu(fdf->mlx);
 	draw_image(fdf);
	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
	{
		mlx_close_window(fdf->mlx);
		ft_free_tab((void **)fdf->map->map2d, fdf->map->cols);
		ft_free_tab((void **)fdf->map->map3d, fdf->map->cols);
		free(fdf->map);
		free(fdf);
		handle_error(mlx_strerror(mlx_errno));
	}
	mlx_loop_hook(fdf->mlx, &ft_hook, fdf);
	mlx_loop_hook(fdf->mlx, &ft_hook_rotate, fdf);
	mlx_loop_hook(fdf->mlx, &ft_hook_project, fdf);
	mlx_scroll_hook(fdf->mlx, &fdf_scrollhook, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	return (0);
}
