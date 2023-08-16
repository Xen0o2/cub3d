/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:13:33 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 11:14:34 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_wall(t_game *game)
{
	game->player->r.distT = game->player->r.distT
		* cos(game->player->r.ca);
	game->player->r.lineH = (MAP_S * (WINDOW_HEIGHT))
		/ game->player->r.distT;
	game->player->r.ty_step
		= (float)game->player->r.texture->height
		/ (float)game->player->r.lineH;
	game->player->r.ty_off = 0;
	if (game->player->r.lineH > WINDOW_HEIGHT)
	{
		game->player->r.ty_off
			= (game->player->r.lineH - WINDOW_HEIGHT) / 2.0;
		game->player->r.lineH = WINDOW_HEIGHT;
	}
	game->player->r.lineO = WINDOW_HEIGHT / 2 - game->player->r.lineH / 2;
}

void	draw(t_game *game)
{
	int	y;

	draw_line(game,
		create_point(game->player->r.r, 0),
		create_point(game->player->r.r, game->player->r.lineO),
		game->C_COLOR);
	y = 0;
	while (y < game->player->r.lineH)
	{
		get_pixel_color(game);
		mlx_put_pixel(game->mlx_img, game->player->r.r,
			y + game->player->r.lineO,
			create_rgba(game->player->r.color.r,
				game->player->r.color.g,
				game->player->r.color.b, game->player->r.color.a));
		game->player->r.ty += game->player->r.ty_step;
		y++;
	}
	draw_line(game,
		create_point(game->player->r.r,
			game->player->r.lineO + game->player->r.lineH),
		create_point(game->player->r.r, WINDOW_HEIGHT),
		game->F_COLOR);
}

void	draw_walls(t_game *game)
{	
	game->player->r.ra = game->player->angle - DR * 30;
	fix_value(&game->player->r.ra);
	game->player->r.r = 0;
	while (game->player->r.r < 480)
	{
		calc_rays(game);
		define_texture(game);
		game->player->r.ca = game->player->angle - game->player->r.ra;
		fix_value(&game->player->r.ca);
		calc_wall(game);
		get_texture(game);
		draw(game);
		game->player->r.r++;
		game->player->r.ra += DR / 8;
		fix_value(&game->player->r.ra);
	}
}
