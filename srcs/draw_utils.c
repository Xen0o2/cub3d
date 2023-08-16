/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:44:58 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 10:51:38 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fix_value(float *value)
{
	if (*value < 0)
		*value += 2 * PI;
	if (*value > 2 * PI)
		*value -= 2 * PI;
}

void	calc_rays(t_game *game)
{
	game->player->r.distH = 1000000;
	game->player->r.distV = 1000000;
	draw_horizontal_rays(game);
	draw_vertical_rays(game);
}

void	get_pixel_color(t_game *game)
{
	game->player->r.pixel = ((int)game->player->r.ty
			* game->player->r.texture->height
			+ (int)game->player->r.tx) * 4;
	game->player->r.color.r
		= game->player->r.texture->pixels[game->player->r.pixel];
	game->player->r.color.g
		= game->player->r.texture->pixels[game->player->r.pixel + 1];
	game->player->r.color.b
		= game->player->r.texture->pixels[game->player->r.pixel + 2];
	game->player->r.color.a
		= game->player->r.texture->pixels[game->player->r.pixel + 3];
}
