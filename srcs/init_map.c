/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:16:04 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/25 09:54:54 by alecoutr         ###   ########.fr       */
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

void	refill_map(t_game *game, char **map_copy, char *line, int *i)
{
	int	x;
	int	j;

	x = -1;
	j = 0;
	while (++x < *i)
	{
		game->map_info->map[x] = ft_strdup(map_copy[x]);
		if (!game->map_info->map[x])
			(void)0, free(line), free_all(game->map_info->map), free_all(map_copy), exit_error("Error\nMalloc failed during parsing\n", game);
	}
	free_all(map_copy);
	game->map_info->map[x] = malloc((game->map_info->width + 1) * sizeof(char));
	if (!game->map_info->map[x])
		(void)0, free(line), free_all(game->map_info->map), exit_error("Error\nMalloc failed during parsing\n", game);
	while (line[j])
	{
		if (line[j] == ' ')
			game->map_info->map[x][j] = '#';
		else if (is_map_character(line[j]))
			game->map_info->map[x][j] = line[j];
		else
			(void)0, free(line), free_all(game->map_info->map), exit_error("Error\nInvalid character in map\n", game);
	}
	while (j < game->map_info->width)
		game->map_info->map[x][j++] = '#';
	game->map_info->map[x][j] = 0;
	free(line);	
}

void	realloc_map(t_game *game, char *line, int *i)
{
	char	**map_copy;
	int		length;

	write(1, "appelle\n", 8);
	map_copy = ft_strrdup(game->map_info->map);
	if (!map_copy)
		(void)0, free(line), free_all(game->map_info->map), exit_error("Error\nMalloc failed during parsing\n", game);
	write(1, "init copy ok\n", 13);
	length = ft_strlen(line);
	free(game->map_info->map);
	printf("Nouvelle hauteur de carte %d\n", *i + 1);
	game->map_info->map = malloc((*i + 1) * sizeof(char **));
	if (!game->map_info->map)
		(void)0, free(line), free_all(map_copy), exit_error("Error\nMalloc failed during parsing\n", game);
	if (length > game->map_info->width)
		game->map_info->width = length;
	printf("fin realloc");
	refill_map(game, map_copy, line, i);
}

void	init_map(t_game *game)
{
	char	*line;
	int		i;
	int		length;

	
	line = get_first_wall(game);
	i = 0;
	length = 0;
	printf("premier mur '%s'\n", line);
	game->map_info->map = malloc(sizeof(char **));
	if (!game->map_info->map)
		exit_error("Error\nMalloc failed during parsing\n", game);
	while (line)
	{
		printf("je fais '%s'\n", line);
		realloc_map(game, line, &i);
		line = get_next_line(game->fd);
	}
	game->map_info->height = i;
}
