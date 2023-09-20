/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:31:03 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/20 17:06:36 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	init_map(map_t *map)
{
	malloc_map(map);
	map->interval = ft_min(WIDTH / map->cols, HEIGHT / map->rows) / 2;
	map->interval = ft_max(2.0, map->interval);
	map->alpha = 0.46373398 / 2;
	map->beta = 0.46373398;
	map->rotate_x = 0;
	map->rotate_y = 0;
	map->rotate_z = 0;
	map->x_offset = 0;
	map->y_offset = 0;
	map->z_divisor = 1;
	map->use_zcolor = false;
	map->low = 0;
	map->high = 0;
}

static map_t	*parse_input(char *filename)
{
	int		fd;
	map_t	*map;

 	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
		handle_error("Unable to open file");
	map = malloc(sizeof(map_t));
	if (!map)
	{
		close(fd);
		handle_error(MALLOC);
	}
	get_cols(fd, map);
	get_rows(fd, map);
	if (map->cols == 0 || map->rows == 0)
		error_map(fd);
	close(fd);
	init_map(map);
	fd = open(filename, O_RDONLY, 0777);
	parse_map(fd, map);
	close(fd);
	set_zcolor(map);
	return (map);
}

static fdf_t	*init_fdf(char *filename)
{
	map_t			*map;
	mlx_t			*mlx;
	mlx_image_t		*image;
	static fdf_t	fdf;
	
	map = parse_input(filename);
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		handle_error(mlx_strerror(mlx_errno));
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image)
	{
		mlx_close_window(mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	fdf.mlx = mlx;
	fdf.image = image;
	fdf.map = map;
	return (&fdf);
}

int32_t	main(int ac, char **av)
{
	fdf_t		*fdf;

	if (ac != 2 || !valid_filename(av[1]))
		handle_error(FORMAT);
	fdf = init_fdf(av[1]);
	display_menu(fdf->mlx);
 	draw_image(fdf);
	if (mlx_image_to_window(fdf->mlx, fdf->image, 0, 0) == -1)
	{
		mlx_close_window(fdf->mlx);
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
