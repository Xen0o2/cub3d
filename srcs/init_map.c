/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:16:04 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/15 16:48:11 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_first_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_whitespace(line[i]))
		i++;
	return (line[i] == '1');
}

char	*get_first_wall(t_game *game)
{
	char	*line;
	
	line = get_next_line(game->fd);
	while (line && is_empty(line))
		(void)0, free(line), line = get_next_line(game->fd);
	if (!line)
		exit_error("Error\nInvalid map 1\n", game);
	if (!is_first_wall(line))
		(void)0, free(line), exit_error("Error\nInvalid map 2\n", game);
	return (line);
}

int	is_map_character(char c)
{
	return (c == '0'
		|| c == ' '
		|| c == '1'
		|| c == 'N'
		|| c == 'S'
		|| c == 'E'
		|| c == 'W');
}

void    append_to_map(t_game *game, char *line, int i)
{
    char	**copy;
	int		x;

	copy = malloc((i + 2)  * sizeof(char *));
	if (!copy)
		(void)0, free(line), exit_error("Error\nMalloc failed during parsing\n", game);
	x = 0;
	while (x < i)
	{
		copy[x] = game->map_info->map[x];
		x++;
	}
	copy[x] = ft_strdup(line);
	copy[x + 1] = 0;
	free(game->map_info->map);
	game->map_info->map = copy;
}

void	fill_map(t_game *game)
{
	char    *line;
    int        i;
    int        length;
    
    line = get_first_wall(game);
    game->map_info->map = malloc(sizeof(char *));
    if (!game->map_info->map)
        (void)0, free(line), exit_error("Error\nMalloc failed during parsing\n", game);
	game->map_info->map[0] = 0;
    i = 0;
    length = 0;
    while(line)
    {
        append_to_map(game, line, i);
        length = ft_strlen(line);
        if (length > game->map_info->width)
            game->map_info->width = length;
        free(line);
        line = get_next_line(game->fd);
        i++;
    }
	free(line);
    game->map_info->height = i;
}

int	is_valid_char(t_game *game, int i, int x)
{
	if (!is_map_character(game->map_info->map[i][x]))
		return (0);
	if (game->map_info->map[i][x] != '0')
		return (1);
	if (i == 0 || !game->map_info->map[i - 1][x] || game->map_info->map[i - 1][x] == ' '
		|| !game->map_info->map[i][x - 1] || game->map_info->map[i][x - 1] == ' '
		|| !game->map_info->map[i + 1] || !game->map_info->map[i + 1][x] || game->map_info->map[i + 1][x] == ' '
		|| !game->map_info->map[i][x + 1] || game->map_info->map[i][x + 1] == ' ')
			return (0);
	return (1);
}

void	define_spawn(t_game *game, int i, int x)
{
	char	c;

	c = game->map_info->map[i][x];
	game->player->position.y = i * 64 + 32;
	game->player->position.x = x * 64 + 32;
	if (c == 'N')
		game->player->angle = deg_to_rad(270);
	else if (c == 'E')
		game->player->angle = deg_to_rad(0);
	else if (c == 'S')
		game->player->angle = deg_to_rad(90);
	else if (c == 'W')
		game->player->angle = deg_to_rad(180);
	game->player->delta.x = cos(game->player->angle) * 5;
	game->player->delta.y = sin(game->player->angle) * 5;
}

void	verif_map(t_game *game)
{
	int		i;
	int		x;
	char	c;

	i = 0;
	while (game->map_info->map[i])
	{
		x = 0;
		while (game->map_info->map[i][x])
		{
			if (!is_valid_char(game, i, x))
				exit_error("Error\nInvalid map\n", game);
			c = game->map_info->map[i][x];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				if (game->player->position.x == 0)
					define_spawn(game, i, x);
				else
					exit_error("Error\nMultiple spawn point\n", game);
			}
			x++;
		}
		i++;
	}
	if (game->player->position.x == 0)
		exit_error("Error\nNo spawn point defined\n", game);
}

void    init_map(t_game *game)
{
	fill_map(game);
	verif_map(game);
}
