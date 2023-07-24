/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:16:07 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/22 21:41:41 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	verif_args(int ac, char **av, t_game *game)
{
	char	*extension;
	int		fd;

	if (ac != 2)
		exit_error("Error\nUsage: ./cub3d <map.cub>\n");
	extension = ft_substr(av[1], ft_strlen(av[1]) - 4, 4);
	if (ft_strcmp(extension, ".cub"))
	{
		free(extension);
		exit_error("Error\nUsage: ./cub3d <map.cub>\n");
	}
	free(extension);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_error("Error\nCan't open map file\n");
	else
		game->fd = fd;
}

void	init_game(t_game *game)
{
	game->NO_TEXTURE = NULL;
	game->SO_TEXTURE = NULL;
	game->WE_TEXTURE = NULL;
	game->EA_TEXTURE = NULL;
	game->F_COLOR = NULL;
	game->C_COLOR = NULL;
	parse_parameters(game);
}

void	parse_parameters(t_game *game)
{
	char	*line;
	char	**infos;
	int		count;

	line = get_next_line(game->fd);
	count = 0;
	while (line)
	{
		if (is_empty(line))
			continue ;
		infos = ft_split(line, ' ');
		if (ft_strrlen(infos) == 2)
			count += update_parameter(game, infos);
		free_all(infos);
		if (count == 6)
			break ;
		free(line);
		line = get_next_line(game->fd);
	}
	free(line);
	if (count != 6 || parameter_is_null(game))
		(void)0, free_parameters(game), exit_error("Error\nInvalid parameters\n");
}

int	parameter_is_null(t_game *game)
{
	return (game->NO_TEXTURE == NULL
		|| game->SO_TEXTURE == NULL
		|| game->WE_TEXTURE == NULL
		|| game->EA_TEXTURE == NULL
		|| game->F_COLOR == NULL
		|| game->C_COLOR == NULL);
}

int	update_parameter(t_game *game, char **infos)
{
	if (!ft_strcmp(infos[0], "NO"))
		return (game->NO_TEXTURE = ft_strdup(infos[1]), 1);
	else if (!ft_strcmp(infos[0], "SO"))
		return (game->SO_TEXTURE = ft_strdup(infos[1]), 1);
	else if (!ft_strcmp(infos[0], "WE"))
		return (game->WE_TEXTURE = ft_strdup(infos[1]), 1);
	else if (!ft_strcmp(infos[0], "EA"))
		return (game->EA_TEXTURE = ft_strdup(infos[1]), 1);
	else if (!ft_strcmp(infos[0], "F"))
		return (game->F_COLOR = ft_strdup(infos[1]), 1);
	else if (!ft_strcmp(infos[0], "C"))
		return (game->C_COLOR = ft_strdup(infos[1]), 1);
	return (0);
}
