/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:30:52 by mwallage          #+#    #+#             */
/*   Updated: 2023/09/07 18:40:40 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/inc/libft.h"

# define	WIDTH	1920
# define	HEIGHT	1080

# define TEXT_COLOR			0xEAEAEAFF
# define BACKGROUND			0x222222FF
# define MENU_BACKGROUND	0x1E1E1E00

# define COLOR_TEN			0xFFFFFFFF
# define COLOR_NINE			0xfff7fbFF
# define COLOR_EIGHT		0xece2f0FF
# define COLOR_SEVEN		0xd0d1e6FF
# define COLOR_SIX			0xa6bddbFF
# define COLOR_FIVE			0x67a9cfFF
# define COLOR_FOUR			0x3690c0FF
# define COLOR_THREE		0x02818aFF
# define COLOR_TWO			0x016c59FF
# define COLOR_ONE			0x014636FF

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
	double			interval;
	double			alpha;
	double			beta;
	point3d_t		**map3d;
	point2d_t		**map2d;
}					map_t;

typedef struct	ft_hook_s
{
	mlx_t		*mlx;
	map_t		*map;
	mlx_image_t	*image;
}			ft_hook_t;

/* fdf_parse.c */
void		parse_map(int, map_t *);
int			valid_filename(const char *);
void		get_cols(int, map_t *);
void		get_rows(int, map_t *);
map_t		*parse_input(int, char **);

/* fdf_error.c */
void		handle_error(const char *);
void		error_map(int, map_t *);

/* fdf_draw.c */
void		draw_grid(mlx_image_t *image, map_t *map);
void		draw_lines(mlx_image_t *image, map_t *map);
void		draw_image(mlx_image_t *image, map_t *map);
void		draw_reset(mlx_image_t *image);

/* fdf_project.c */
void		iso_project(map_t *map);

/* fdf_hooks.c */
void		ft_hook(void* param);

/* fdf_utils.c*/
void		ft_free_tab(void **ptr);
double		percent(int start, int end, int current);
void		make_upper(unsigned int i, char *c);

/* fdf_color.c */
int			project_color(map_t *map, int i, int j);
int			get_light(int start, int end, double percentage);
int			get_color(point2d_t current, point2d_t a, point2d_t b, int dx, int dy);
int			parse_color(char *tabj);
void		set_zcolor(map_t *map);

#endif
