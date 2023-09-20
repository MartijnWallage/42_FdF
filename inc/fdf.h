/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:30:52 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/20 16:52:56 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/inc/libft.h"

# define	WIDTH	1920
# define	HEIGHT	1080

# define TEXT_COLOR			0xEAEAEAFF
# define BACKGROUND			0x22222200
# define MENU_BACKGROUND	0x1E1E1EFF

# define COLOR_TEN			0x9e0142ff
# define COLOR_NINE			0xd53e4fff
# define COLOR_EIGHT		0xf46d43ff
# define COLOR_SEVEN		0xfdae61ff
# define COLOR_SIX			0xfee08bff
# define COLOR_FIVE			0xe6f598ff
# define COLOR_FOUR			0xabdda4ff
# define COLOR_THREE		0x66c2a5ff
# define COLOR_TWO			0x3288bdff
# define COLOR_ONE			0x5e4fa2ff

# define FORMAT				"Format:\n\t./fdf maps/filename.fdf"
# define MALLOC				"Malloc failed"
# define INVALID_MAP		"Map is invalid"

typedef struct	point3d_s
{
	double	x;
	double	y;
	double	z;
	int		mapcolor;
	int		zcolor;
}				point3d_t;

typedef struct	point2d_s
{
	int		x;
	int		y;
	int		z;
	int		rgba;
}			point2d_t;

typedef struct map_s
{
	int				rows;
	int				cols;
	int				high;
	int				low;
	bool			use_zcolor;
	double			x_offset;
	double			y_offset;
	double			z_divisor;
	double			interval;
	double			alpha;
	double			beta;
	double			rotate_x;
	double			rotate_y;
	double			rotate_z;
	point3d_t		**map3d;
	point2d_t		**map2d;
}					map_t;

typedef struct	fdf_s
{
	mlx_t		*mlx;
	map_t		*map;
	mlx_image_t	*image;
}				fdf_t;

/* fdf_parse.c */
void		parse_map(int, map_t *);
int			valid_filename(const char *);
void		get_cols(int, map_t *);
void		get_rows(int, map_t *);
void		malloc_map(map_t *map);

/* fdf_error.c */
void		handle_error(const char *message);
void		error_map(int fd);

/* fdf_draw.c */
void		draw_lines(mlx_image_t *image, map_t *map);
void		draw_image(fdf_t *fdf);
void		draw_reset(mlx_image_t *image);

/* fdf_project.c */
void		project(map_t *map, int i, int j);

/* fdf_rotate.c */
void		rotate_all(map_t *map, char axis, double alpha);

/* fdf_hooks.c */
void		ft_hook(void* param);
void		fdf_scrollhook(double xdelta, double ydelta, void* param);
void		ft_hook_rotate(void *param);
void		ft_hook_project(void *param);

/* fdf_utils.c*/
void		ft_free_tab(void **ptr, size_t len);
double		percent(int start, int end, int current);
void		make_upper(unsigned int i, char *c);
int			radiant(int start, int end, double percentage);

/* fdf_color.c */
int			get_light(int start, int end, double percentage);
int			get_color(point2d_t current, point2d_t a, point2d_t b);
int			parse_color(char *tabj);
void		set_zcolor(map_t *map);

/* fdf_menu.c */
void		display_menu(mlx_t *mlx);

#endif
