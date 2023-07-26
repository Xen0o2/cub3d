/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:39:38 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/26 11:21:01 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 512

typedef struct s_map_info
{
	char	**map;
	int		height;
	int		width;	
}	t_map_info;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_player
{
	t_point	position;
}	t_player;

typedef struct s_game
{
	t_map_info	*map_info;
	t_player	*player;
	mlx_t		*mlx;
	mlx_image_t	*mlx_img;
	char		*NO_TEXTURE;
	char		*SO_TEXTURE;
	char		*WE_TEXTURE;
	char		*EA_TEXTURE;
	char		*F_COLOR;
	char		*C_COLOR;
	int			fd;
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

void	exit_error(char *message, t_game *game);

// INIT
void	verif_args(int ac, char **av, t_game *game);
void	init_parameters(t_game *game);
void	parse_parameters(t_game *game);
int		parameter_is_null(t_game *game);
int		update_parameter(t_game *game, char **infos);
void	init_map(t_game *game);


// FREE
void	free_all(char **tab);
void	free_parameters(t_game *game);

// UTILS
int		ft_strcmp(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
int		ft_strlen(char *str);
int		ft_strrlen(char **strr);
char	*ft_strdup(char *s1);
char	**ft_strrdup(char **s1);
char	*ft_strchr(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int		is_whitespace(char c);
int		is_empty(char *line);

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

#endif
