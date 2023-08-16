/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:36:44 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 09:31:05 by alecoutr         ###   ########.fr       */
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
	game->player->ray.r = 0;
	game->player->ray.mx = 0;
	game->player->ray.my = 0;
	game->player->ray.dof = 0;
}

void	init_default_values2(t_game *game)
{
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
	game->player->ray.distT = 0;
	game->player->in_game = 0;
	game->draw_minimap = 1;
	game->player->ray.lineH = 0;
	game->player->ray.lineO = 0;
	game->player->ray.ca = 0;
	game->player->ray.ty_step = 0;
	game->player->ray.ty_off = 0;
	game->player->ray.texture = NULL;
	game->player->ray.ty = 0;
	game->player->ray.tx = 0;
	game->player->ray.pixel = 0;
	init_default_values3(game);
}

void	init_default_values3(t_game *game)
{
	game->player->ray.color.r = 0;
	game->player->ray.color.g = 0;
	game->player->ray.color.b = 0;
	game->player->ray.color.a = 0;
	game->map_info->minimap_square_size = SQUARE_MAP_SIZE;
	game->window_height = WINDOW_HEIGHT;
	game->window_width = WINDOW_WIDTH;
}
