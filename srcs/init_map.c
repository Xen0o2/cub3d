/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:16:04 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/25 12:02:14 by alecoutr         ###   ########.fr       */
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
		(void)0, free(line), line = get_next_line(game->fd), printf("ligne vide\n");
	if (!line)
		exit_error("Error\nInvalid map\n", game);
	if (!is_first_wall(line))
		(void)0, free(line), exit_error("Error\nInvalid map\n", game);
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

void	init_map(t_game *game)
{
	char	*line;
	int		i;
	int		length;

	
	line = get_first_wall(game);
}
