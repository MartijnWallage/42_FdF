/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:37:23 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/24 15:16:53 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	parse_map(int fd, map_t *map)
{
	char		*line;
	char		*current;
	int32_t		x;
	int32_t 	y;
	point3d_t	*points;

	points = map->map3d;
	y = -1;
	ft_printf("map->rows: %d, map->cols: %d\n", map->rows, map->cols);
	while (++y < map->rows)
	{
 		line = get_next_line(fd);
		if (!line)
			error_map(fd, map, NULL);
		// use ft_split to get tab of each point.
		current = line;
		x = -1;
		while (++x < map->cols)
		{
			if (!ft_isdigit(*current))
				error_map(fd, map, line);
			points->x = (map->interval) * x;
			points->y = (map->interval) * y;
			points->z = ft_atoi(current);
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

int	valid_filename(const char *filename)
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
	(map->map3d) = malloc(sizeof(point3d_t) * ((map->rows) * (map->cols) + 1));
	if (!map->map3d)
	{
		free(map);
		handle_error("mlx: malloc failed");
	}
	map->map3d[map->rows * map->cols] = NULL;
	map->interval = ft_min(WIDTH, HEIGHT) / ft_max(map->cols, map->rows);
	fd = open(av[1], O_RDONLY, 0777);
	parse_map(fd, map);
	close(fd);
	return (map);
}