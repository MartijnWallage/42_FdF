/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:37:23 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/30 15:05:27 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	parse_color(int fd, t_map *map, char *tabj)
{
	while (*tabj == '-')
		tabj++;
	while (ft_isdigit(*tabj))
		tabj++;
	if (*tabj == ',')
		tabj++;
	else
		return (0xFFFFFFFF);
	if ((ft_strncmp(tabj, "0X", 2) && ft_strncmp(tabj, "0x", 2)))
		error_map(fd, map, INVALID_MAP);
	tabj += 2;
	ft_striteri(tabj, &make_upper);
	return ((ft_atoi_base(tabj, "0123456789ABCDEF") << 8) | 0xFF);
}

static void	parse_column(int fd, t_map *map, char **tab, int i)
{
	t_point3d	*point;
	int			x_offset;
	int			y_offset;
	int			j;

	j = -1;
	while (++j < map->cols)
	{
		if (!ft_isdigit(*tab[j]) && *tab[j] != '-')
			error_map(fd, map, INVALID_MAP);
		point = &(map->grid3d[i][j]);
		x_offset = (map->cols - 1) * map->interval / 2;
		y_offset = (map->rows - 1) * map->interval / 2;
		point->x = (double)j * (map->interval) - x_offset;
		point->y = (double)i * (map->interval) - y_offset;
		point->z = (double)ft_atoi(tab[j]) * (map->interval);
		map->high = ft_max(map->high, point->z);
		map->low = ft_min(map->low, point->z);
		point->mapcolor = parse_color(fd, map, tab[j]);
	}
}

void	parse_map(int fd, t_map *map)
{
	char	*line;
	char	*temp;
	char	**tab;
	int		i;

	i = -1;
	while (++i < map->rows)
	{
		temp = get_next_line(fd);
		if (!temp)
			error_map(fd, map, MALLOC);
		line = ft_strtrim(temp, "\n");
		free(temp);
		if (!line)
			error_map(fd, map, MALLOC);
		tab = ft_split(line, ' ');
		free(line);
		if (!tab)
			error_map(fd, map, MALLOC);
		parse_column(fd, map, tab, i);
		ft_free_tab((void **)tab, map->cols);
	}
}

static int	get_cols(int fd, t_map *map, char *line)
{
	char	**tab;
	char	*temp;
	int		i;

	temp = ft_strtrim(line, "\n");
	free(line);
	if (!temp)
		error_map(fd, map, MALLOC);
	tab = ft_split(temp, ' ');
	free(temp);
	if (!tab)
		error_map(fd, map, MALLOC);
	i = 0;
	while (tab[i])
	{
		map->high = ft_max(map->high, ft_atoi(tab[i]));
		map->low = ft_min(map->low, ft_atoi(tab[i]));
		i++;
	}
	ft_free_tab((void **)tab, i);
	return (i);
}

void	get_dimensions(int fd, t_map *map)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		error_map(fd, map, MALLOC);
	map->cols = get_cols(fd, map, line);
	if (map->cols == 0)
		error_map(fd, map, INVALID_MAP);
	map->rows = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map->rows++;
		if (map->cols != get_cols(fd, map, line))
			error_map(fd, map, INVALID_MAP);
	}
}
