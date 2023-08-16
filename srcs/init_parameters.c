/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:16:07 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/15 11:43:10 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_parameters(t_game *game)
{
	game->map_info = malloc(sizeof(t_map_info));
	if (!game->map_info)
		exit_error("Error\nMalloc failed\n", game);
	game->map_info->map = 0;
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		exit_error("Error\nMalloc failed\n", game);
	init_default_values(game);
	init_default_values2(game);
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
		while (line && is_empty(line))
			(void)0, free(line), line = get_next_line(game->fd);
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
		exit_error("Error\nInvalid parameters\n", game);
	verif_parameters(game);
}

int	parameter_is_null(t_game *game)
{
	return (game->NO_TEXTURE_CHAR == NULL
		|| game->SO_TEXTURE_CHAR == NULL
		|| game->WE_TEXTURE_CHAR == NULL
		|| game->EA_TEXTURE_CHAR == NULL
		|| game->F_COLOR_CHAR == NULL
		|| game->C_COLOR_CHAR == NULL);
}

int	update_parameter(t_game *game, char **infos)
{
	if (!ft_strcmp(infos[0], "NO"))
		return (game->NO_TEXTURE_CHAR = ft_strdup(infos[1]), 1);
	else if (!ft_strcmp(infos[0], "SO"))
		return (game->SO_TEXTURE_CHAR = ft_strdup(infos[1]), 1);
	else if (!ft_strcmp(infos[0], "WE"))
		return (game->WE_TEXTURE_CHAR = ft_strdup(infos[1]), 1);
	else if (!ft_strcmp(infos[0], "EA"))
		return (game->EA_TEXTURE_CHAR = ft_strdup(infos[1]), 1);
	else if (!ft_strcmp(infos[0], "F"))
		return (game->F_COLOR_CHAR = ft_strdup(infos[1]), 1);
	else if (!ft_strcmp(infos[0], "C"))
		return (game->C_COLOR_CHAR = ft_strdup(infos[1]), 1);
	return (0);
}
