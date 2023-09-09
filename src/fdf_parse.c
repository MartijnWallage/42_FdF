/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:37:23 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/09 17:56:32 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	parse_map(int fd, map_t *map)
{
	char		*line;
	char		**tab;
	int			i;
	int			j;
	point3d_t	**points;
	double		offset_x;
	double		offset_y;

	offset_x = (map->cols - 1) * map->interval / 2;
	offset_y = (map->rows - 1) * map->interval / 2;
	points = map->map3d;
	i = -1;
	while (++i < map->rows)
	{
 		line = get_next_line(fd);
		if (!line)
			error_map(fd, map);
		tab = ft_split(line, ' ');
		free(line);
		j = -1;
		while (++j < map->cols)
		{
			if (!ft_isdigit(*tab[j]) && *tab[j] != '-')
				error_map(fd, map);
			points[i][j].x = (double) j * (map->interval) - offset_x;
			points[i][j].y = (double) i * (map->interval) - offset_y;
			points[i][j].z = (double) ft_atoi(tab[j]) * (map->interval);
			map->low = ft_min(map->low, points[i][j].z);
			map->high = ft_max(map->high, points[i][j].z);
			points[i][j].mapcolor = parse_color(tab[j]);
			if (!points[i][j].mapcolor)
				error_map(fd, map);
		}
		ft_free_tab((void **)tab);
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
	char	**tab;
	int		i;
	int		j;
	
	line = get_next_line(fd);
	if (!line)
		error_map(fd, map);
	tab = ft_split(line, ' ');
	free(line);
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] == ' ')
			j++;
		if (tab[i][j] == '\n')
			break ;	
		i++;
	}
	map->cols = i;
	ft_free_tab((void *)tab);
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

static void	malloc_map(map_t	*map)
{
	int	i;
	int j;
	
	map->map3d = malloc(sizeof(point3d_t *) * map->rows);
	if (!(map->map3d))
	{
		free(map);
		handle_error(strerror(errno));
	}
	map->map2d = malloc(sizeof(point2d_t *) * map->rows);
	if (!(map->map2d))
	{
		free(map);
		handle_error(strerror(errno));
	}
	i = -1;
	while (++i < map->rows)
	{
		map->map3d[i] = malloc(sizeof(point3d_t) * map->cols);
		if (!(map->map3d[i]))
		{
			j = -1;
			while (++j < i)
			{
				free(map->map3d[j]);
				free(map->map2d[j]);
			}
			free(map->map2d);
			free(map->map3d);
			free(map);
			handle_error(strerror(errno));
		}
		map->map2d[i] = malloc(sizeof(point2d_t) * map->cols);
		if (!(map->map2d[i]))
		{
			j = -1;
			while (++j < i)
			{
				free(map->map2d[j]);
				free(map->map3d[j]);
			}
			free(map->map3d[i]);
			free(map->map2d);
			free(map->map3d);
			free(map);
			handle_error(strerror(errno));
		}
	}
}

void	init_map(map_t *map)
{
	malloc_map(map);
	map->interval = ft_min(WIDTH / map->cols, HEIGHT / map->rows) / 2;
	map->interval = ft_max(2.0, map->interval);
	map->projection = 'i';
	map->alpha = 0.46373398;
	map->beta = 0.46373398 / 2;
	map->rotate_x = 0;
	map->rotate_y = 0;
	map->rotate_z = 0;
	map->x_offset = 0;
	map->y_offset = 0;
	map->use_zcolor = false;
	map->low = 0;
	map->high = 0;
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
		error_map(fd, map);
	close(fd);
	init_map(map);
	fd = open(av[1], O_RDONLY, 0777);
	parse_map(fd, map);
	close(fd);
	set_zcolor(map);
	return (map);
}