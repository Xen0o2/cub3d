/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:43:43 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 11:12:39 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	define_texture(t_game *game)
{
	if (game->player->r.distV < game->player->r.distH)
	{
		game->player->r.rx = game->player->r.vx;
		game->player->r.ry = game->player->r.vy;
		game->player->r.distT = game->player->r.distV;
		if (game->player->r.ra > deg_to_rad(90)
			&& game->player->r.ra < deg_to_rad(270))
			game->player->r.texture = game->WE_TEXTURE;
		else
			game->player->r.texture = game->EA_TEXTURE;
	}
	else
	{
		game->player->r.rx = game->player->r.hx;
		game->player->r.ry = game->player->r.hy;
		game->player->r.distT = game->player->r.distH;
		if (game->player->r.ra > deg_to_rad(0)
			&& game->player->r.ra < deg_to_rad(180))
			game->player->r.texture = game->SO_TEXTURE;
		else
			game->player->r.texture = game->NO_TEXTURE;
	}
}

void	get_texture(t_game *game)
{
	game->player->r.ty = game->player->r.ty_off * game->player->r.ty_step;
	if (game->player->r.distH < game->player->r.distV)
	{
		game->player->r.tx
			= (int)(game->player->r.rx / 2.0)
			% game->player->r.texture->width;
		if (game->player->r.ra < deg_to_rad(180))
			game->player->r.tx = 31 - game->player->r.tx;
	}
	else
	{	
		game->player->r.tx
			= (int)(game->player->r.ry / 2.0)
			% game->player->r.texture->width;
		if (game->player->r.ra > deg_to_rad(90)
			&& game->player->r.ra < deg_to_rad(270))
			game->player->r.tx = 31 - game->player->r.tx;
	}
}
