/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:41:05 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 10:41:50 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horizontal_condition(t_game *game, float atan)
{
	if (game->player->r.ra > PI)
	{
		game->player->r.ry
			= (((int)game->player->position.y / MAP_S) * MAP_S)
			- 0.0001;
		game->player->r.rx = (game->player->position.y
				- game->player->r.ry) * atan + game->player->position.x;
		game->player->r.yo = -MAP_S;
		game->player->r.xo = -game->player->r.yo * atan;
	}
	else if (game->player->r.ra < PI)
	{
		game->player->r.ry = (((int)game->player->position.y
					/ MAP_S) * MAP_S) + MAP_S;
		game->player->r.rx = (game->player->position.y
				- game->player->r.ry) * atan + game->player->position.x;
		game->player->r.yo = MAP_S;
		game->player->r.xo = -game->player->r.yo * atan;
	}
	else
	{
		game->player->r.ry = game->player->position.y;
		game->player->r.rx = game->player->position.x;
		game->player->r.dof = MAX_DOF;
	}	
}

void	find_horizontal_wall(t_game *game)
{
	game->player->r.mx = (int)(game->player->r.rx) / MAP_S;
	game->player->r.my = (int)(game->player->r.ry) / MAP_S;
	if (game->player->r.mx >= 0 && game->player->r.my >= 0
		&& game->player->r.mx < game->map_info->width
		&& game->player->r.my < game->map_info->height
		&& game->map_info->map[game->player->r.my][game->player->r.mx] == '1')
	{
		game->player->r.hx = game->player->r.rx;
		game->player->r.hy = game->player->r.ry;
		game->player->r.distH = distance(
				create_point(game->player->position.x,
					game->player->position.y),
				create_point(game->player->r.hx, game->player->r.hy));
		game->player->r.dof = MAX_DOF;
	}
	else
	{
		game->player->r.rx += game->player->r.xo;
		game->player->r.ry += game->player->r.yo;
		game->player->r.dof++;
	}
}

void	draw_horizontal_rays(t_game *game)
{
	float	atan;

	atan = -1 / tan(game->player->r.ra);
	game->player->r.dof = 0;
	game->player->r.hx = game->player->position.x;
	game->player->r.hy = game->player->position.y;
	horizontal_condition(game, atan);
	while (game->player->r.dof < MAX_DOF)
		find_horizontal_wall(game);
}
