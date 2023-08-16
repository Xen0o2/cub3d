/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:39:38 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 16:14:34 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define WINDOW_WIDTH 480
# define WINDOW_HEIGHT 320

# define SQUARE_MAP_SIZE 64
# define MAX_DOF 150
# define MAP_S 64

# define PI 3.1415926535
# define P2 PI / 2
# define P3 3 * PI / 2
# define DR 0.0174533

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

typedef struct s_map_info
{
	char	**map;
	int		height;
	int		width;
	int		minimap_square_size;
}	t_map_info;


typedef struct s_ray
{
	int				r;
	int				mx;
	int				my;
	int				dof;
	int				ixo;
	int				iyo;
	int				ipx;
	int				ipy;
	int				ipx_add_ixo;
	int				ipx_sub_ixo;
	int				ipy_add_iyo;
	int				ipy_sub_iyo;
	float			rx;
	float			ry;
	float			ra;
	float			xo;
	float			yo;
	float			distH;
	float			hx;
	float			hy;
	float			distV;
	float			vx;
	float			vy;
	float			distT;
	float			lineH;
	float			lineO;
	float			ca;
	float			ty_step;
	float			ty_off;
	mlx_texture_t *texture;
	float 			ty;
	float 			tx;
	int 			pixel;
	t_color 		color;
}	t_ray;

typedef struct s_player
{
	t_point	position;
	t_point	delta;
	t_ray	r;
	float	angle;
	int		in_game;
	int		speed;
}	t_player;


typedef struct s_game
{
	int				window_height;
	int				window_width;
	t_map_info		*map_info;
	t_player		*player;
	int				draw_minimap;
	mlx_t			*mlx;
	mlx_image_t		*mlx_img;
	char			*NO_TEXTURE_CHAR;
	char			*SO_TEXTURE_CHAR;
	char			*WE_TEXTURE_CHAR;
	char			*EA_TEXTURE_CHAR;
	char			*F_COLOR_CHAR;
	char			*C_COLOR_CHAR;
	mlx_texture_t	*NO_TEXTURE;
	mlx_texture_t	*SO_TEXTURE;
	mlx_texture_t	*WE_TEXTURE;
	mlx_texture_t	*EA_TEXTURE;
	unsigned long	F_COLOR;
	unsigned long	C_COLOR;
	int				fd;
}	t_game;

typedef struct s_join
{
	char	*result;
	int		i;
	int		x;
}	t_join;

typedef struct s_split
{
	char	**tab;
	int		i;
	int		j;
	int		sep;
	int		length;
}	t_split;

// KEY HOOK
void	key_hook(mlx_key_data_t keydata, void *param);
void    collision(t_game *game);
void    rotate_key(t_game *game, mlx_key_data_t keydata);
void    move_key(t_game *game, mlx_key_data_t keydata);

// HOOK
void	hook(void *param);
void	rotate_mouse(t_game *game);

// RESIZE HOOK
void	resize_hook(int32_t width, int32_t height, void *param);

// MOUSE HOOK
void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param);

// INIT
void	init_game(t_game *game, int ac, char **av);
void	init_window(t_game *game);
void	init_parameters(t_game *game);
void	init_default_values(t_game *game);
void	init_default_values2(t_game *game);
void	init_default_values3(t_game *game);
void	load_render(t_game *game);
void	parse_parameters(t_game *game);
int		parameter_is_null(t_game *game);
int		update_parameter(t_game *game, char **infos);

// INIT MAP
void	init_map(t_game *game);
char	*get_first_wall(t_game *game);
int		is_first_wall(char *line);
int		is_map_character(char c);
void    append_to_map(t_game *game, char *line, int i);
void	fill_map(t_game *game);
int		is_valid_char(t_game *game, int i, int x);
void	define_spawn(t_game *game, int i, int x);

// VERIF
void			verif_args(int ac, char **av, t_game *game);
void			verif_parameters(t_game *game);
unsigned long	verif_color(t_game *game, char *color);
mlx_texture_t	*verif_texture(t_game *game, char *texture_path);

// WALLS
void	draw_walls(t_game *game);

// MINIMAP
void	draw_tile(t_game *game, int square_size, int x, int y);
void	draw_minimap(t_game *game);

// PLAYER
void	draw_player(t_game *game);

// DRAW
void	draw_line(t_game *game, t_point begin, t_point end, int color);
void	draw_square(t_game *game, t_point points[2], int color);
t_point	create_point(float x, float y);

// DRAW UTILS
void	fix_value(float *value);
void	calc_rays(t_game *game);
void	get_pixel_color(t_game *game);


// HORIZONTAL RAYS
void	draw_horizontal_rays(t_game *game);
void	horizontal_condition(t_game *game, float atan);
void	find_horizontal_wall(t_game *game);

// VERTICAL RAYS
void	draw_vertical_rays(t_game *game);
void	vertical_condition(t_game *game, float ntan);
void	find_vertical_wall(t_game *game);

// TEXTURE
void	define_texture(t_game *game);
void	get_texture(t_game *game);


// UTILS
int				ft_strcmp(char *s1, char *s2);
char			*ft_substr(char *s, int start, int len);
int				ft_strlen(char *str);
int				ft_strrlen(char **strr);
char			*ft_strdup(char *s1);
char			**ft_strrdup(char **s1);
char			*ft_strchr(char *s, char c);
char			*ft_strjoin(char *s1, char *s2);
int				is_whitespace(char c);
int				is_empty(char *line);
float			deg_to_rad(float degree);
float			ft_abs(int value);
float			distance(t_point p1, t_point p2);
int				is_digit(char *str);
long long int	ft_atoi(const char *s);
unsigned long 	create_rgba(int r, int g, int b, int a);
float			fix_ang(float a);

// GET_NEXT_LINE
char	*ft_read(int fd, char *all);
char	*get_one_line(char *all);
char	*get_rest(char *all);
char	*get_next_line(int fd);

// SPLIT
int	next_word_length(char *s, char c);
int	get_sep_nbr(char *s, char c);
char	*create_malloc(char **tab, int length);
char	**ft_freeall(char **tab, int length);
char	**ft_split(char *s, char c);

// FREE
void	free_all(char **tab);
void	free_parameters(t_game *game);

// EXIT
void	exit_error(char *message, t_game *game);
void	exit_success(t_game *game);

#endif
