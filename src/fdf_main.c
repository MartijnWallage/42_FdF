/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:31:03 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/27 20:59:23 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	malloc_grid(t_map *map)
{
	int	i;

	map->map3d = malloc(sizeof(t_point3d *) * map->rows);
	if (!(map->map3d))
		handle_error(MALLOC);
	map->map2d = malloc(sizeof(t_point2d *) * map->rows);
	if (!(map->map2d))
		handle_error(MALLOC);
	i = -1;
	while (++i < map->rows)
	{
		map->map3d[i] = malloc(sizeof(t_point3d) * map->cols);
		if (!(map->map3d[i]))
			handle_error(MALLOC);
		map->map2d[i] = malloc(sizeof(t_point2d) * map->cols);
		if (!(map->map2d[i]))
			handle_error(MALLOC);
	}
}

void	init_map(t_map *map)
{
	map->alpha = 0.46373398 / 2;
	map->beta = 0.46373398;
	map->xrotate = 0;
	map->zrotate = 0;
	map->x_offset = WIDTH / 2;
	map->y_offset = HEIGHT / 2;
	map->zoom = 1;
	map->zscale = 1;
	map->use_zcolor = false;
}

static t_map	*parse_input(char *filename)
{
	int		fd;
	t_map	*map;

	fd = open(filename, O_RDONLY, 0777);
	if (fd == -1)
		handle_error(FILE_ERROR);
	map = malloc(sizeof(t_map));
	if (!map)
		handle_error_fd(fd, MALLOC);
	init_map(map);
	get_dimensions(fd, map);
	if (map->cols == 0 || map->rows == 0)
		error_map(fd);
	close(fd);
	malloc_grid(map);
	map->interval = ft_min(WIDTH / map->cols, HEIGHT / map->rows) / 2;
	if (map->high - map->low > 0)
		map->interval = ft_min(map->interval,
				HEIGHT / (map->high - map->low) / 2);
	map->interval = ft_max(2, map->interval);
	fd = open(filename, O_RDONLY, 0777);
	parse_map(fd, map);
	close(fd);
	set_zcolor(map);
	return (map);
}

static t_fdf	*init_fdf(char *filename)
{
	static t_fdf	fdf;

	fdf.map = parse_input(filename);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!fdf.mlx)
		handle_error(mlx_strerror(mlx_errno));
	fdf.image = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.image)
	{
		mlx_close_window(fdf.mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	return (&fdf);
}

int32_t	main(int ac, char **av)
{
	t_fdf		*fdf;

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
	mlx_loop_hook(fdf->mlx, &draw_image, fdf);
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	return (0);
}
