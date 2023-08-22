/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:31:03 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/22 16:18:11 by mwallage         ###   ########.fr       */
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
map_t	*parse_map(int fd, map_t *map)
{
	char	*line;
	char	*current;
	int32_t	x;
	int32_t y;

	y = -1;
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
			map->map2d->x = x++;
			map->map2d->y = y;
			map->map2d->value = ft_atoi(current);
			while (ft_isdigit(*current))
				current++;
			if (*current == ',')
			{
				if (ft_strncmp(current, "0x", 2))
					error_map(fd, map, line);
				map->map2d->rgba = ft_atoi(current);
				current += 2;
				while (ft_isdigit(*current))
					current++;
			}
			while (*current == ' ' || *current == '\t')
				current++;
		}
		free(line);
	}
	return (map);
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
	map->map2d = malloc(sizeof(map_t) * map->rows * map->cols);
	if (!map->map2d)
	{
		free(map);
		handle_error("mlx: malloc failed");
	}
	fd = open(av[1], O_RDONLY, 0777);
	parse_map(fd, map);
	close(fd);
	return (map);
}

void	draw_image(mlx_image_t *image, map_t *map)
{
	uint32_t	i;
	uint32_t	j;

	if (!map)
		i = 0;
	i = -1;
	while (++i < (uint32_t)(map->cols * 10))
	{
		j = -1;
		while (++j < (uint32_t)(map->rows * 10))
			mlx_put_pixel(image, i, j, 0xFFFFFF);
	}
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

	map = parse_input(ac, av);
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		handle_error(mlx_strerror(mlx_errno));
	image = mlx_new_image(mlx, map->cols * 10, map->rows * 10);
	if (!image)
	{
		mlx_close_window(mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	draw_image(image, map);
	if (mlx_image_to_window(mlx, image, 10, 10) == -1)
	{
		mlx_close_window(mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
