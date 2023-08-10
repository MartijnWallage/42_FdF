/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:31:03 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/10 17:38:52 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	handle_error(const char *message)
{
	ft_putendl_fd((char *)message, 2);
	exit(1);
}

int	open_fdf(char *arg)
{
	char	*filepath;
	int		fd;

	filepath = ft_strjoin("maps/", arg);
	if (!filepath)
		return (-1);
	fd = open(filepath, O_RDONLY, 0777);
	free(filepath);
	return (fd);
}

map_t	*parse_map(int fd)
{
	char	*line;
	map_t	*map;

	map = malloc(sizeof(map));
	if (!map)
		handle_error("malloc failed");
	line = get_next_line(fd);
	if (!line)
	{
		free(map);
		handle_error("malloc failed");
	}
	free(line);
	return (map);
}

map_t	*parse_input(int ac, char **av)
{
	map_t	*map;
	int		fd;

	if (ac != 2 || ! ft_strnstr(av[1], ".fdf", ft_strlen(av[1])))
		handle_error("Format:\n\t./fdf *.fdf");
	fd = open_fdf(av[2]);
	if (fd == -1)
		return (NULL);
	map = parse_map(fd);
	close(fd);
	return (map);
}

void	draw_image(mlx_image_t *image)
{
	uint32_t	i;
	uint32_t	j;

	i = -1;
	while (++i < image->width)
	{
		j = -1;
		while (++j < image->height)
		{
			mlx_put_pixel(image, i, j, 0xFFFFFF);
		}
	}
}

int32_t	main(int ac, char **av)
{
	mlx_t	*mlx;
	mlx_image_t	*image;
	map_t	*map;

	map = parse_input(ac, av);
	if (!map)
		handle_error("bad input");
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		handle_error(mlx_strerror(mlx_errno));
	image = mlx_new_image(mlx, 128, 128);
	if (!image)
	{
		mlx_close_window(mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	draw_image(image);
	if (mlx_image_to_window(mlx, image, 10, 10) == -1)
	{
		mlx_close_window(mlx);
		handle_error(mlx_strerror(mlx_errno));
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
