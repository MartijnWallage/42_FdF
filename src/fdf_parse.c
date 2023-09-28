/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:37:23 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/27 15:43:05 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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
			error_map(fd);
		point = &(map->map3d[i][j]);
		x_offset = (map->cols - 1) * map->interval / 2;
		y_offset = (map->rows - 1) * map->interval / 2;
		point->x = (double)j * (map->interval) - x_offset;
		point->y = (double)i * (map->interval) - y_offset;
		point->z = (double)ft_atoi(tab[j]) * (map->interval);
		map->high = ft_max(map->high, point->z);
		map->low = ft_min(map->low, point->z);
		point->mapcolor = parse_color(fd, tab[j]);
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
			handle_error_fd(fd, MALLOC);
		line = ft_strtrim(temp, "\n");
		free(temp);
		if (!line)
			handle_error_fd(fd, MALLOC);
		tab = ft_split(line, ' ');
		free(line);
		if (!tab)
			handle_error_fd(fd, MALLOC);
		parse_column(fd, map, tab, i);
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

static int	get_cols(int fd, t_map *map, char *line)
{
	char	**tab;
	char	*temp;
	int		i;

	temp = ft_strtrim(line, "\n");
	if (!temp)
		handle_error_fd(fd, MALLOC);
	tab = ft_split(temp, ' ');
	free(temp);
	if (!tab)
		handle_error_fd(fd, MALLOC);
	map->high = INT_MIN;
	map->low = INT_MAX;
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
	int		y;

	line = get_next_line(fd);
	if (!line || *line == '\0' || *line == '\n')
		error_map(fd);
	map->cols = get_cols(fd, map, line);
	y = 1;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if (map->cols != get_cols(fd, map, line))
			error_map(fd);
		y++;
	}
	map->rows = y;
}
