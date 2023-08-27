/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:37:23 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/26 17:15:54 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	parse_map(int fd, map_t *map)
{
	char		*line;
	char		**tab;
	int			i;
	int 		j;
	point3d_t	**points;

	points = map->map3d;
	i = -1;
	while (++i < map->rows)
	{
 		line = get_next_line(fd);
		if (!line)
			error_map(fd, map, NULL);
		tab = ft_split(line, ' ');
		j = -1;
		while (++j < map->cols)
		{
			if (!ft_isdigit(*tab[j]) && *tab[j] != '-')
				error_map(fd, map, line);
			points[i][j].y = (double) (j * (map->interval));
			points[i][j].x = (double) (i * (map->interval));
			points[i][j].z = (double) (ft_atoi(tab[j]) * (map->interval / 4));
			points[i][j].rgba = 0xFFFFFF;
		}
		ft_free_tab((void **)tab);
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
	while (ft_isdigit(*current) || *current == '-')
	{
		x++;
		while (ft_isdigit(*current) || *current == '-')
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

static void	malloc_map3d(map_t	*map)
{
	int	i;
	int j;
	
	map->map3d = malloc(sizeof(point3d_t *) * map->rows);
	if (!(map->map3d))
	{
		free(map);
		handle_error("malloc error");
	}
	i = -1;
	while (++i < map->rows)
	{
		map->map3d[i] = malloc(sizeof(point3d_t) * map->cols);
		if (!(map->map3d[i]))
		{
			j = -1;
			while (++j < i)
				free(map->map3d[j]);
			free(map);
			handle_error("malloc error");
		}
	}
}

map_t	*parse_input(int ac, char **av)
{
	int		fd;
	map_t	*map;

	if (ac != 2 || !valid_filename(av[1]))
		handle_error("Format:\n\t./fdf *.fdf");
 	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
		handle_error("mlx: file does not exist.");
	map = malloc(sizeof(map_t));
	if (!map)
		handle_error("malloc error");
	get_cols(fd, map);
	get_rows(fd, map);
	if (map->cols == 0 || map->rows == 0)
		error_map(fd, map, "mlx: map is empty");
	close(fd);
	malloc_map3d(map);
	map->interval = ft_min(WIDTH / map->cols, HEIGHT / map->rows) / 2;
	fd = open(av[1], O_RDONLY, 0777);
	parse_map(fd, map);
	close(fd);
	return (map);
}