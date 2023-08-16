/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:06:21 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 11:07:18 by alecoutr         ###   ########.fr       */
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

char	*get_first_wall(t_game *game)
{
	char	*line;

	line = get_next_line(game->fd);
	while (line && is_empty(line))
		(void)0, free(line), line = get_next_line(game->fd);
	if (!line)
		exit_error("Error\nInvalid map\n", game);
	if (!is_first_wall(line))
		(void)0, free(line), exit_error("Error\nInvalid map\n", game);
	return (line);
}

void	append_to_map(t_game *game, char *line, int i)
{
	char	**copy;
	int		x;

	copy = malloc((i + 2) * sizeof(char *));
	if (!copy)
		(void)0, free(line),
			exit_error("Error\nMalloc failed during parsing\n", game);
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
