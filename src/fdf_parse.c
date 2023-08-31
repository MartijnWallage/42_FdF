/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:37:23 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/31 13:02:09 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	make_upper(unsigned int i, char *c)
{
	i++;
	*c = ft_toupper(*c);
}

int	parse_color(char *tabj)
{
	while (*tabj == '-')
		tabj++;
	while (ft_isdigit(*tabj))
		tabj++;
	if (*tabj == ',')
		tabj++;
	else
		return (0xFF0000FF);
	if ((ft_strncmp(tabj, "0X", 2) && ft_strncmp(tabj, "0x", 2)))
		return (-1);
	tabj += 2;
	ft_striteri(tabj, &make_upper);
	return (ft_atoi_base(tabj, "0123456789ABCDEF"));
}

void	parse_map(int fd, map_t *map)
{
	char		*line;
	char		**tab;
	int			i;
	int			j;
	point3d_t	**points;
	double		offset_x;
	double		offset_y;

	offset_x = -(map->cols - 1) * map->interval / 2;
	offset_y = -(map->rows - 1) * map->interval / 2;
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
			points[i][j].x = (double) j * (map->interval) + offset_x;
			points[i][j].y = (double) i * (map->interval) + offset_y;
			points[i][j].z = (double) ft_atoi(tab[j]) * (map->interval / 4);
			points[i][j].rgba = parse_color(tab[j]);
			if (points[i][j].rgba == -1)
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
	
	line = get_next_line(fd);
	if (!line)
		error_map(fd, map);
	tab = ft_split(line, ' ');
	free(line);
	i = 0;
	while (tab[i])
		i++;
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
		error_map(fd, map);
	close(fd);
	malloc_map3d(map);
	map->interval = ft_min(WIDTH / map->cols, HEIGHT / map->rows) / 4;
	map->alpha = 0.46373398;
	map->beta = 0.46373398 / 2;
	fd = open(av[1], O_RDONLY, 0777);
	parse_map(fd, map);
	close(fd);
	return (map);
}