/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:13:33 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/28 14:41:07 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_game *game)
{
	float	offset;
	float	y;
	float	x;

	offset = 4;
	y = game->player->py - offset - 1;
	
	while (++y < game->player->py + offset)
	{
		x = game->player->px - offset - 1;
		while (++x < game->player->px + offset)
			if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
				mlx_put_pixel(game->mlx_img, x, y, 0xFFFF00FF);	
	}
	draw_line(game, create_point(game->player->px, game->player->py),
					create_point(game->player->px + game->player->delta.x * 5, game->player->py + game->player->delta.y * 5), 0xFFFF00FF);
	draw_ray_3d(game);
}

void	draw_map_2d(t_game *game)
{
	int		y;
	int		x;
	int		square_size;
	t_point	points[2];

	y = 0;
	square_size = 20;
	while (game->map_info->map[y])
	{
		x = 0;
		while (game->map_info->map[y][x])
		{
			points[0] = create_point(x * square_size + 1, y * square_size + 1);
			points[1] = create_point(x * square_size + square_size - 1, y * square_size + square_size - 1);
			if (game->map_info->map[y][x] == '1')
				draw_square(game, points, 0xFFFFFFFF);
			else if (game->map_info->map[y][x] == '0')
				draw_square(game, points, 0x000000FF);
			x++;
		}
		y++;
	}
}

void	draw_ray_3d(t_game *game)
{
	float	aTan;
	
	game->player->ray.ra = game->player->angle;
	game->player->ray.r = 0;
	while (game->player->ray.r < 1)
	{
		game->player->ray.dof = 0;
		aTan = -1 / tan(game->player->ray.ra);
		if (game->player->ray.ra > PI)
		{
			game->player->ray.ry = (((int)game->player->py >> 6) << 6) - 0.0001;
			game->player->ray.rx = (game->player->py - game->player->ray.ry) * aTan + game->player->px;
			game->player->ray.yo = -64;
			game->player->ray.xo = -game->player->ray.yo * aTan;
		}
		if (game->player->ray.ra < PI)
		{
			game->player->ray.ry = (((int)game->player->py >> 6) << 6) + 64;
			game->player->ray.rx = (game->player->py - game->player->ray.ry) * aTan + game->player->px;
			game->player->ray.yo = 64;
			game->player->ray.xo = -game->player->ray.yo * aTan;
		}
		if (game->player->ray.ra == 0 || game->player->ray.ra == PI)
		{
			printf("je mets %f %f\n", game->player->px, game->player->py);
			game->player->ray.rx = game->player->px;
			game->player->ray.ry = game->player->py;
			game->player->ray.dof = 8;
		}
		while (game->player->ray.dof < 8)
		{
			game->player->ray.mx = (int)(game->player->ray.rx) >> 6;
			game->player->ray.my = (int)(game->player->ray.ry) >> 6;
			if (game->map_info->map[game->player->ray.my] && game->map_info->map[game->player->ray.my][game->player->ray.mx] == '1')
				game->player->ray.dof = 8;
			else
			{
				game->player->ray.rx += game->player->ray.xo;
				game->player->ray.ry += game->player->ray.yo;
				game->player->ray.dof += 1;
			}
		}
		draw_line(game, create_point(game->player->px, game->player->py), create_point(game->player->ray.mx, game->player->ray.my), 0x00ff00ff);
		game->player->ray.r++;
	}
}
