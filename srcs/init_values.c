/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:36:44 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 10:39:16 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_default_values(t_game *game)
{
	game->NO_TEXTURE_CHAR = NULL;
	game->SO_TEXTURE_CHAR = NULL;
	game->WE_TEXTURE_CHAR = NULL;
	game->EA_TEXTURE_CHAR = NULL;
	game->F_COLOR_CHAR = NULL;
	game->C_COLOR_CHAR = NULL;
	game->NO_TEXTURE = NULL;
	game->SO_TEXTURE = NULL;
	game->WE_TEXTURE = NULL;
	game->EA_TEXTURE = NULL;
	game->F_COLOR = 0;
	game->C_COLOR = 0;
	game->map_info->height = 0;
	game->map_info->width = 0;
	game->player->position.x = 0;
	game->player->position.y = 0;
	game->player->angle = deg_to_rad(90);
	game->player->speed = 5;
	game->player->delta.x = cos(game->player->angle) * game->player->speed;
	game->player->delta.y = sin(game->player->angle) * game->player->speed;
	game->player->r.r = 0;
	game->player->r.mx = 0;
	game->player->r.my = 0;
	game->player->r.dof = 0;
}

void	init_default_values2(t_game *game)
{
	game->player->r.rx = 0;
	game->player->r.ry = 0;
	game->player->r.ra = 0;
	game->player->r.xo = 0;
	game->player->r.yo = 0;
	game->player->r.distH = 1000000;
	game->player->r.hx = 0;
	game->player->r.hy = 0;
	game->player->r.distV = 1000000;
	game->player->r.vx = 0;
	game->player->r.vy = 0;
	game->player->r.distT = 0;
	game->player->in_game = 0;
	game->draw_minimap = 1;
	game->player->r.lineH = 0;
	game->player->r.lineO = 0;
	game->player->r.ca = 0;
	game->player->r.ty_step = 0;
	game->player->r.ty_off = 0;
	game->player->r.texture = NULL;
	game->player->r.ty = 0;
	game->player->r.tx = 0;
	game->player->r.pixel = 0;
	init_default_values3(game);
}

void	init_default_values3(t_game *game)
{
	game->player->r.color.r = 0;
	game->player->r.color.g = 0;
	game->player->r.color.b = 0;
	game->player->r.color.a = 0;
	game->map_info->minimap_square_size = SQUARE_MAP_SIZE;
	game->window_height = WINDOW_HEIGHT;
	game->window_width = WINDOW_WIDTH;
}
