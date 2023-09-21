/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:37:23 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/21 15:22:04 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	parse_map_helper(t_map *map, char *tabj, int x, int y)
{
	t_point3d	*point;
	int			x_offset;
	int			y_offset;

	point = &(map->map3d[y][x]);
	x_offset = (map->cols - 1) * map->interval / 2;
	y_offset = (map->rows - 1) * map->interval / 2;
	point->x = (double)x * (map->interval) - x_offset;
	point->y = (double)y * (map->interval) - y_offset;
	point->z = (double)ft_atoi(tabj) * (map->interval);
	map->low = ft_min(map->low, point->z);
	map->high = ft_max(map->high, point->z);
	point->mapcolor = parse_color(tabj);
}

void	parse_map(int fd, t_map *map)
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
			parse_map_helper(map, tab[j], j, i);
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

void	get_cols(int fd, t_map *map)
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

void	get_rows(int fd, t_map *map)
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
