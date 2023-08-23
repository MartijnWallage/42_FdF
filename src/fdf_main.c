/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:31:03 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/23 17:54:54 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	handle_error(const char *message)
{
	ft_putendl_fd((char *)message, 2);
	exit(1);
}

void	error_map(int fd, map_t *map, char *line)
{
	close(fd);
	free(map);
	if (line)
		free(line);
	handle_error("mlx: invalid map.");
}

void	parse_map(int fd, map_t *map)
{
	char		*line;
	char		*current;
	int32_t		x;
	int32_t 	y;
	point2d_t	*points;

	points = map->map2d;
	y = -1;
	ft_printf("map->rows: %d, map->cols: %d\n", map->rows, map->cols);
	while (++y < map->rows)
	{
 		line = get_next_line(fd);
		if (!line)
			error_map(fd, map, NULL);
		current = line;
		x = -1;
		while (++x < map->cols)
		{
			if (!ft_isdigit(*current))
				error_map(fd, map, line);
			points->x = (map->interval) * x;
			points->y = (map->interval) * y;
			points->value = ft_atoi(current);
			while (ft_isdigit(*current))
				current++;
			if (*current == ',')
			{
				if (ft_strncmp(current, "0x", 2))
					error_map(fd, map, line);
				points->rgba = ft_atoi(current);
				current += 2;
				while (ft_isdigit(*current))
					current++;
			}
			points++;
			while (*current == ' ' || *current == '\t')
				current++;
		}
		free(line);
	}
}

static int	valid_filename(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	filename += len - 4;
	return (ft_strncmp(filename, ".fdf", 4) == 0);
}

void	get_cols(int fd, map_t *map)
{
	char	*line;
	char	*current;
	int		x;
	
	line = get_next_line(fd);
	if (!line)
		error_map(fd, map, NULL);
	x = 0;
	current = line;
	while (ft_isdigit(*current))
	{
		x++;
		while (ft_isdigit(*current))
			current++;
		if (*line == ',')
		{
			if (ft_strncmp(current, "0x", 2))
				error_map(fd, map, line);
			current += 2;
			while (ft_isdigit(*current))
				current++;
		}
		while (*current == ' ' || *current == '\t')
			current++;
	}
	free(line);
	map->cols = x;
}

void	get_rows(int fd, map_t *map)
{
	char	*line;
	int		y;

	y = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line || *line == '\0')
			break ;
		y++;
		free(line);
	}
	map->rows = y;
}

map_t	*parse_input(int ac, char **av)
{
	map_t	*map;
	int		fd;

	if (ac != 2 || !valid_filename(av[1]))
		handle_error("Format:\n\t./fdf *.fdf");
 	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
		handle_error("mlx: file does not exist.");
	map = malloc(sizeof(map_t));
	if (!map)
	{
		close(fd);
		handle_error("mlx: malloc failed");
	}
	get_cols(fd, map);
	get_rows(fd, map);
	close(fd);
	(map->map2d) = malloc(sizeof(point2d_t) * (map->rows) * (map->cols));
	if (!map->map2d)
	{
		free(map);
		handle_error("mlx: malloc failed");
	}
	map->interval = ft_min(WIDTH, HEIGHT) / ft_max(map->cols, map->rows);
	fd = open(av[1], O_RDONLY, 0777);
	parse_map(fd, map);
	close(fd);
	return (map);
}

void	draw_grid(mlx_image_t *image, map_t *map)
{
	point2d_t	*points;
	int			i;

	points = map->map2d;
	i = -1;
	while (++i < (map->rows) * (map->cols))
	{
		mlx_put_pixel(image, points->x, points->y, 0xFFFFFFFF);
		points++;
	}
}

void	draw_lines(mlx_image_t *image, map_t *map)
{
	uint32_t	i;
	uint32_t	j;
	
	i = -1;
	while (++i <= (map->rows - 1) * (map->interval))
	{
		j = -1;
		while (++j <= (map->cols - 1) * (map->interval))
		{
			if (i % map->interval == 0 || j % map->interval == 0)
				mlx_put_pixel(image, j, i, 0xEEDDFFFF);
		}
	}	
}

void	draw_image(mlx_image_t *image, map_t *map)
{
	draw_grid(image, map);
	draw_lines(image, map);
}

void ft_hook(void* param)
{
	mlx_t* mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int32_t	main(int ac, char **av)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	map_t		*map;
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
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
