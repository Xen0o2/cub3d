/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:13:33 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 09:59:51 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_game *game)
{
	t_point	points[2];
	int		square_size;

	square_size = 3;
	if (game->map_info->height > 50 || game->map_info->width > 50)
		square_size = 1;
	points[0] = create_point(
		(game->player->position.x / 64 * square_size + 10) - 1,
		(game->player->position.y / 64 * square_size + 10) - 1);
	points[1] = create_point(
		(game->player->position.x / 64 * square_size + 10) + 1,
		(game->player->position.y / 64 * square_size + 10) + 1);
	draw_square(game, points, 0xFF0000FF);
}

void	draw_tile(t_game *game, int square_size, int x, int y)
{
	t_point	points[2];
	int		color;
	
	points[0] = create_point(x * square_size + 10, y * square_size + 10);
			points[1] = create_point(x * square_size + square_size + 10,
					y * square_size + square_size + 10);
			if (game->C_COLOR > 0xFFFFFFFF / 2)
				color = 0x000000FF;
			else
				color = 0xFFFFFFFF;
			if (game->map_info->map[y][x] == '1')
				draw_square(game, points, game->C_COLOR);
			if (is_map_character(game->map_info->map[y][x])
					&& game->map_info->map[y][x] != ' '
					&& game->map_info->map[y][x] != '1')
				draw_square(game, points, color);
}

void	draw_minimap(t_game *game)
{
	int		y;
	int		x;
	int		square_size;

	y = 0;
	square_size = 3;
	if (game->map_info->height > 50 || game->map_info->width > 50)
		square_size = 3;
	while (game->map_info->map[y])
	{
		x = 0;
		while (game->map_info->map[y][x])
			draw_tile(game, square_size, x++, y);
		y++;
	}
	draw_player(game);
}

void	fix_value(float *value)
{
	if (*value < 0)
		*value += 2 * PI;
	if (*value > 2 * PI)
		*value -= 2 * PI;	
}

void	draw_rays(t_game *game)
{	
	int	y;
	game->player->ray.ra = game->player->angle - DR * 30;
	fix_value(&game->player->ray.ra);
	
	game->player->ray.r = 0;
	while (game->player->ray.r < 480)
	{
		game->player->ray.distH = 1000000;
		game->player->ray.distV = 1000000;
		draw_horizontal_rays(game);
		draw_vertical_rays(game);
		if (game->player->ray.distV < game->player->ray.distH)
		{
			game->player->ray.rx = game->player->ray.vx;
			game->player->ray.ry = game->player->ray.vy;
			game->player->ray.distT = game->player->ray.distV;
			if (game->player->ray.ra > deg_to_rad(90) && game->player->ray.ra < deg_to_rad(270))
				game->player->ray.texture = game->WE_TEXTURE;
			else
				game->player->ray.texture = game->EA_TEXTURE;
		}
		else
		{
			game->player->ray.rx = game->player->ray.hx;
			game->player->ray.ry = game->player->ray.hy;
			game->player->ray.distT = game->player->ray.distH;
			if (game->player->ray.ra > deg_to_rad(0) && game->player->ray.ra < deg_to_rad(180))
				game->player->ray.texture = game->SO_TEXTURE;
			else
				game->player->ray.texture = game->NO_TEXTURE;
		}
		
		game->player->ray.ca = game->player->angle - game->player->ray.ra;
		fix_value(&game->player->ray.ca);
		game->player->ray.distT = game->player->ray.distT * cos(game->player->ray.ca);
		game->player->ray.lineH = (MAP_S * (WINDOW_HEIGHT)) / game->player->ray.distT;
		game->player->ray.ty_step = (float)game->player->ray.texture->height / (float)game->player->ray.lineH;
		game->player->ray.ty_off = 0;
		if (game->player->ray.lineH > WINDOW_HEIGHT)
		{
			game->player->ray.ty_off = (game->player->ray.lineH - WINDOW_HEIGHT) / 2.0;
			game->player->ray.lineH = WINDOW_HEIGHT;
		}
		game->player->ray.lineO = WINDOW_HEIGHT / 2 - game->player->ray.lineH / 2;
		//sky
		draw_line(game, create_point(game->player->ray.r, 0), create_point(game->player->ray.r, game->player->ray.lineO), game->C_COLOR);
		//walls

		game->player->ray.ty = game->player->ray.ty_off * game->player->ray.ty_step;
		if (game->player->ray.distH < game->player->ray.distV)
		{
			game->player->ray.tx = (int)(game->player->ray.rx / 2.0) % game->player->ray.texture->width;
			if (game->player->ray.ra < deg_to_rad(180))
				game->player->ray.tx = 31 - game->player->ray.tx;
		}
		else
		{	
			game->player->ray.tx = (int)(game->player->ray.ry / 2.0) % game->player->ray.texture->width;
			if (game->player->ray.ra > deg_to_rad(90) && game->player->ray.ra < deg_to_rad(270))
				game->player->ray.tx = 31 - game->player->ray.tx;
		}
		y = 0;
		while (y < game->player->ray.lineH)
		{
			game->player->ray.pixel = ((int)game->player->ray.ty * game->player->ray.texture->height + (int)game->player->ray.tx) * 4;
			game->player->ray.color.r = game->player->ray.texture->pixels[game->player->ray.pixel];
			game->player->ray.color.g = game->player->ray.texture->pixels[game->player->ray.pixel + 1];
			game->player->ray.color.b = game->player->ray.texture->pixels[game->player->ray.pixel + 2];
			game->player->ray.color.a = game->player->ray.texture->pixels[game->player->ray.pixel + 3];
			mlx_put_pixel(game->mlx_img, game->player->ray.r, y + game->player->ray.lineO, create_RGBA(game->player->ray.color.r,game->player->ray.color.g,game->player->ray.color.b,game->player->ray.color.a));
			game->player->ray.ty += game->player->ray.ty_step;
			y++;
		}
		draw_line(game, create_point(game->player->ray.r, game->player->ray.lineO + game->player->ray.lineH), create_point(game->player->ray.r, WINDOW_HEIGHT), game->F_COLOR);
		game->player->ray.r++;
		game->player->ray.ra += DR / 8;
		fix_value(&game->player->ray.ra);
	}
}

void	draw_horizontal_rays(t_game *game)
{
	float	a_tan;

	a_tan = -1 / tan(game->player->ray.ra);
	game->player->ray.dof = 0;
	game->player->ray.hx = game->player->position.x;
	game->player->ray.hy = game->player->position.y;
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
	game->player->ray.dof = 0;
	game->player->ray.vx = game->player->position.x;
	game->player->ray.vy = game->player->position.y;
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
		{
			game->player->ray.vx = game->player->ray.rx;
			game->player->ray.vy = game->player->ray.ry;
			game->player->ray.distV = distance(create_point(game->player->position.x, game->player->position.y), create_point(game->player->ray.vx, game->player->ray.vy));
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
