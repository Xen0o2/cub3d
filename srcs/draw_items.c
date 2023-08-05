/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:13:33 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/05 11:46:59 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_game *game)
{
	float	offset;
	float	y;
	float	x;

	draw_rays(game);
	offset = 4;
	y = game->player->position.y - offset - 1;
	
	while (++y < game->player->position.y + offset)
	{
		x = game->player->position.x - offset - 1;
		while (++x < game->player->position.x + offset)
			if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
				mlx_put_pixel(game->mlx_img, x, y, 0xFFFF00FF);	
	}
	draw_line(game, create_point(game->player->position.x, game->player->position.y),
					create_point(game->player->position.x + game->player->delta.x * 5, game->player->position.y + game->player->delta.y * 5), 0xFFFF00FF);
}

void	draw_minimap(t_game *game)
{
	int		y;
	int		x;
	int		square_size;
	t_point	points[2];

	y = 0;
	square_size = SQUARE_MAP_SIZE;
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

void	draw_rays(t_game *game)
{
	game->player->ray.r = 0;
	while (game->player->ray.r < 1)
	{
		draw_horizontal_rays(game);
		draw_vertical_rays(game);
		game->player->ray.r++;
	}
}

void	draw_horizontal_rays(t_game *game)
{
	float	a_tan;

	game->player->ray.hx = game->player->position.x;
	game->player->ray.hy = game->player->position.y;
	game->player->ray.ra = game->player->angle;
	a_tan = -1 / tan(game->player->ray.ra);
	game->player->ray.dof = 0;
	if (game->player->ray.ra > PI)
	{
		game->player->ray.ry = (((int)game->player->position.y / MAP_S) * MAP_S) - 0.0001;
		game->player->ray.rx = (game->player->position.y - game->player->ray.ry) * a_tan + game->player->position.x;
		game->player->ray.yo = -MAP_S;
		game->player->ray.xo = -game->player->ray.yo * a_tan;
	}
	else if (game->player->ray.ra < PI)
	{
		game->player->ray.ry = (((int)game->player->position.y / MAP_S) * MAP_S) + MAP_S;
		game->player->ray.rx = (game->player->position.y - game->player->ray.ry) * a_tan + game->player->position.x;
		game->player->ray.yo = MAP_S;
		game->player->ray.xo = -game->player->ray.yo * a_tan;
	}
	else
	{
		game->player->ray.ry = game->player->position.y;
		game->player->ray.rx = game->player->position.x;
		game->player->ray.dof = MAX_DOF;
	}
	while (game->player->ray.dof < MAX_DOF)
	{
		game->player->ray.mx = (int)(game->player->ray.rx) / MAP_S;
		game->player->ray.my = (int)(game->player->ray.ry) / MAP_S;
		if (game->player->ray.mx >= 0 && game->player->ray.my >= 0 && game->player->ray.mx < game->map_info->width
			&& game->player->ray.my < game->map_info->height
			&& game->map_info->map[game->player->ray.my][game->player->ray.mx] == '1')
		{
			game->player->ray.hx = game->player->ray.rx;
			game->player->ray.hy = game->player->ray.ry;
			game->player->ray.distH = distance(create_point(game->player->position.x, game->player->position.y), create_point(game->player->ray.hx, game->player->ray.hy));
			game->player->ray.dof = MAX_DOF;
		}
		else
		{
			game->player->ray.rx += game->player->ray.xo;
			game->player->ray.ry += game->player->ray.yo;
			game->player->ray.dof++;
		}
	}
}

void    draw_vertical_rays(t_game *game)
{
    float	ntan;

	ntan = -tan(game->player->ray.ra);
	game->player->ray.vx = game->player->position.x;
	game->player->ray.vy = game->player->position.y;
	game->player->ray.dof = 0;
	if (game->player->ray.ra > P2 && game->player->ray.ra < P3)
	{
		game->player->ray.rx = (((int)game->player->position.x / MAP_S) * MAP_S) - 0.0001;
		game->player->ray.ry = (game->player->position.x - game->player->ray.rx) * ntan + game->player->position.y;
		game->player->ray.xo = -MAP_S;
		game->player->ray.yo = -game->player->ray.xo * ntan;
	}
	else if (game->player->ray.ra < P2 || game->player->ray.ra > P3)
	{
		game->player->ray.rx = (((int)game->player->position.x / MAP_S) * MAP_S) + MAP_S;
		game->player->ray.ry = (game->player->position.x - game->player->ray.rx) * ntan + game->player->position.y;
		game->player->ray.xo = MAP_S;
		game->player->ray.yo = -game->player->ray.xo * ntan;
	}
	else
	{
		game->player->ray.ry = game->player->position.y;
		game->player->ray.rx = game->player->position.x;
		game->player->ray.dof = MAX_DOF;
	}
	while (game->player->ray.dof < MAX_DOF)
	{
		game->player->ray.mx = (int)(game->player->ray.rx) / MAP_S;
		game->player->ray.my = (int)(game->player->ray.ry) / MAP_S;
		if (game->player->ray.mx >= 0 && game->player->ray.my >= 0 && game->player->ray.mx < game->map_info->width
			&& game->player->ray.my < game->map_info->height
			&& game->map_info->map[game->player->ray.my][game->player->ray.mx] == '1')
				game->player->ray.dof = MAX_DOF;
		else
		{
			game->player->ray.rx += game->player->ray.xo;
			game->player->ray.ry += game->player->ray.yo;
			game->player->ray.dof++;
		}
	}
}
