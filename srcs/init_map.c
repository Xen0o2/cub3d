/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:16:04 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/26 10:39:57 by alecoutr         ###   ########.fr       */
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

void    init_map(t_game *game)
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
