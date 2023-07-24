/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:39:38 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/22 21:42:24 by alecoutr         ###   ########.fr       */
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

typedef struct s_map_info
{
	char	**map;
	int		height;
	int		width;	
}	t_mapInfo;

typedef struct s_game
{
	t_mapInfo	map_info;
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

void	exit_error(char *message);

// INIT
void	verif_args(int ac, char **av, t_game *game);
void	init_game(t_game *game);
void	parse_parameters(t_game *game);
int		parameter_is_null(t_game *game);
int		update_parameter(t_game *game, char **infos);

// FREE
void	free_all(char **tab);
void	free_parameters(t_game *game);

// UTILS
int		ft_strcmp(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
int		ft_strlen(char *str);
char	*ft_strchr(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strrlen(char **strr);
char	*ft_strdup(char *s1);
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
