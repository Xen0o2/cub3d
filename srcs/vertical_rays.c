/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:42:42 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 10:42:58 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vertical_condition(t_game *game, float ntan)
{
	if (game->player->r.ra > P2 && game->player->r.ra < P3)
	{
		game->player->r.rx = (((int)game->player->position.x
					/ MAP_S) * MAP_S) - 0.0001;
		game->player->r.ry = (game->player->position.x
				- game->player->r.rx) * ntan + game->player->position.y;
		game->player->r.xo = -MAP_S;
		game->player->r.yo = -game->player->r.xo * ntan;
	}
	else if (game->player->r.ra < P2 || game->player->r.ra > P3)
	{
		game->player->r.rx = (((int)game->player->position.x
					/ MAP_S) * MAP_S) + MAP_S;
		game->player->r.ry = (game->player->position.x
				- game->player->r.rx) * ntan + game->player->position.y;
		game->player->r.xo = MAP_S;
		game->player->r.yo = -game->player->r.xo * ntan;
	}
	else
	{
		game->player->r.ry = game->player->position.y;
		game->player->r.rx = game->player->position.x;
		game->player->r.dof = MAX_DOF;
	}
}

void	find_vertical_wall(t_game *game)
{
	game->player->r.mx = (int)(game->player->r.rx) / MAP_S;
	game->player->r.my = (int)(game->player->r.ry) / MAP_S;
	if (game->player->r.mx >= 0 && game->player->r.my >= 0
		&& game->player->r.mx < game->map_info->width
		&& game->player->r.my < game->map_info->height
		&& game->map_info->map[game->player->r.my][game->player->r.mx] == '1')
	{
		game->player->r.vx = game->player->r.rx;
		game->player->r.vy = game->player->r.ry;
		game->player->r.distV = distance(
				create_point(game->player->position.x,
					game->player->position.y),
				create_point(game->player->r.vx, game->player->r.vy));
		game->player->r.dof = MAX_DOF;
	}
	else
	{
		game->player->r.rx += game->player->r.xo;
		game->player->r.ry += game->player->r.yo;
		game->player->r.dof++;
	}
}

void	draw_vertical_rays(t_game *game)
{
	float	ntan;

	ntan = -tan(game->player->r.ra);
	game->player->r.dof = 0;
	game->player->r.vx = game->player->position.x;
	game->player->r.vy = game->player->position.y;
	vertical_condition(game, ntan);
	while (game->player->r.dof < MAX_DOF)
		find_vertical_wall(game);
}
