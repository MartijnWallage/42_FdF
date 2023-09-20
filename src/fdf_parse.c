/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:37:23 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/20 16:56:09 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	parse_map(int fd, map_t *map)
{
	char	*line;
	char	**tab;
	int		i;
	int		j;

	i = -1;
	while (++i < map->rows)
	{
		line = get_next_line(fd);
		if (!line)
			error_map(fd);
		tab = ft_split(line, ' ');
		free(line);
		j = -1;
		while (++j < map->cols)
		{
			if (!ft_isdigit(*tab[j]) && *tab[j] != '-')
				error_map(fd);
			map->map3d[i][j].x = (double)j * (map->interval)
				- (map->cols - 1) * map->interval / 2;
			map->map3d[i][j].y = (double)i * (map->interval)
				- (map->rows - 1) * map->interval / 2;
			map->map3d[i][j].z = (double)ft_atoi(tab[j]) * (map->interval);
			map->low = ft_min(map->low, map->map3d[i][j].z);
			map->high = ft_max(map->high, map->map3d[i][j].z);
			map->map3d[i][j].mapcolor = parse_color(tab[j]);
			if (!map->map3d[i][j].mapcolor)
				error_map(fd);
		}
		ft_free_tab((void **)tab, map->cols);
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
		error_map(fd);
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
	ft_free_tab((void **)tab, i);
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

void	malloc_map(map_t *map)
{
	int	i;
	
	map->map3d = malloc(sizeof(point3d_t *) * map->rows);
	if (!(map->map3d))
		handle_error(MALLOC);
	map->map2d = malloc(sizeof(point2d_t *) * map->rows);
	if (!(map->map2d))
		handle_error(MALLOC);
	i = -1;
	while (++i < map->rows)
	{
		map->map3d[i] = malloc(sizeof(point3d_t) * map->cols);
		if (!(map->map3d[i]))
			handle_error(MALLOC);
		map->map2d[i] = malloc(sizeof(point2d_t) * map->cols);
		if (!(map->map2d[i]))
			handle_error(MALLOC);
	}
}

