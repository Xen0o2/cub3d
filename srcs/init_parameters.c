/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parameters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:16:07 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/05 11:26:03 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	verif_args(int ac, char **av, t_game *game)
{
	char	*extension;
	int		fd;

	if (ac != 2)
		exit_error("Error\nUsage: ./cub3d <map.cub>\n", game);
	extension = ft_substr(av[1], ft_strlen(av[1]) - 4, 4);
	if (ft_strcmp(extension, ".cub"))
	{
		free(extension);
		exit_error("Error\nUsage: ./cub3d <map.cub>\n", game);
	}
	free(extension);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_error("Error\nCan't open map file\n", game);
	else
		game->fd = fd;
}

void	init_parameters(t_game *game)
{
	game->map_info = malloc(sizeof(t_map_info));
	if (!game->map_info)
		exit_error("Error\nMalloc failed\n", game);
	game->map_info->map = 0;
	game->player = malloc(sizeof(t_player));
	if (!game->player)
		exit_error("Error\nMalloc failed\n", game);
	game->NO_TEXTURE = NULL;
	game->SO_TEXTURE = NULL;
	game->WE_TEXTURE = NULL;
	game->EA_TEXTURE = NULL;
	game->F_COLOR = NULL;
	game->C_COLOR = NULL;
	game->map_info->height = 0;
	game->map_info->width = 0;
	game->player->position.x = 80;
	game->player->position.y = 80;
	game->player->angle = deg_to_rad(1);
	game->player->delta.x = cos(game->player->angle) * 5;
	game->player->delta.y = sin(game->player->angle) * 5;
	game->player->ray.r = 0;
	game->player->ray.mx = 0;
	game->player->ray.my = 0;
	game->player->ray.dof = 0;
	game->player->ray.rx = 0;
	game->player->ray.ry = 0;
	game->player->ray.ra = 0;
	game->player->ray.xo = 0;
	game->player->ray.yo = 0;
	game->player->ray.distH = 1000000;
	game->player->ray.hx = 0;
	game->player->ray.hy = 0;
	game->player->ray.distV = 1000000;
	game->player->ray.vx = 0;
	game->player->ray.vy = 0;
	game->map_info->minimap_square_size = SQUARE_MAP_SIZE;
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
