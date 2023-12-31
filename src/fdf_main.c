/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:31:03 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/30 15:50:42 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	malloc_grid(t_map *map)
{
	int	i;

	map->grid3d = malloc(sizeof(t_point3d *) * map->rows);
	map->grid2d = malloc(sizeof(t_point2d *) * map->rows);
	if (!(map->grid2d) || !(map->grid3d))
	{
		free_map(map);
		handle_error(MALLOC);
	}
	i = -1;
	while (++i < map->rows)
	{
		map->grid3d[i] = malloc(sizeof(t_point3d) * map->cols);
		map->grid2d[i] = malloc(sizeof(t_point2d) * map->cols);
		if (!(map->grid2d[i]) || !(map->grid3d[i]))
		{
			if (i + 1 < map->rows)
			{
				map->grid3d[i + 1] = NULL;
				map->grid2d[i + 1] = NULL;
			}
			free_map(map);
			handle_error(MALLOC);
		}
	}
}

void	init_map(t_map *map)
{
	map->alpha = 0.46373398 / 2;
	map->beta = 0.46373398;
	map->xrotate = 0;
	map->yrotate = 0;
	map->zrotate = 0;
	map->x_offset = WIDTH / 2;
	map->y_offset = HEIGHT / 2;
	map->zoom = 1;
	map->zscale = 1;
	map->use_zcolor = false;
	map->high = INT_MIN;
	map->low = INT_MAX;
	map->rows = 0;
	map->cols = 0;
	map->grid2d = NULL;
	map->grid3d = NULL;
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
	{
		close(fd);
		handle_error(MALLOC);
	}
	init_map(map);
	get_dimensions(fd, map);
	close(fd);
	malloc_grid(map);
	map->interval = ft_min(WIDTH / map->cols, HEIGHT / map->rows) / 2;
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
	{
		free_map(fdf.map);
		handle_error(mlx_strerror(mlx_errno));
	}
	fdf.image = mlx_new_image(fdf.mlx, WIDTH, HEIGHT);
	if (!fdf.image)
	{
		free_map(fdf.map);
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
		free_map(fdf->map);
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
	free_map(fdf->map);
	return (0);
}
