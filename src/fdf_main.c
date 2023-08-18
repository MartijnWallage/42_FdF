/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:31:03 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/18 17:27:10 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	handle_error(const char *message)
{
	ft_putendl_fd((char *)message, 2);
	exit(1);
}

map_t	*parse_map(int fd)
{
	char	*line;
	map_t	*map;

	map = malloc(sizeof(map_t));
	if (!map)
	{
		close(fd);
		handle_error("malloc failed");
	}
	while (1)
	{
 		line = get_next_line(fd);
		if (!line)
			break ;
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
 	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
		return (NULL);
	map = parse_map(fd);
	close(fd); 
	map = malloc(sizeof(map_t));
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
	mlx_t		*mlx;
	mlx_image_t	*image;
	map_t		*map;

	map = parse_input(ac, av);
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
