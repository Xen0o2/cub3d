/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:13:33 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/04 16:27:24 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_game *game)
{
	float	offset;
	float	y;
	float	x;

	draw_ray_3d(game);
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

void    horizontal2(t_game *game);

void	draw_ray_3d(t_game *game)
{
    game->player->ray.dof = 0;
	game->player->ray.ra = game->player->angle;
	float	a_tan = -1 / tan(game->player->ray.ra);
	int		map_s = 8;
    if (game->player->ray.ra > PI)
    {
        game->player->ray.ry = (((int)game->player->position.y / map_s) * map_s) - 0.0001;
        game->player->ray.rx = (game->player->position.y - game->player->ray.ry) * a_tan + game->player->position.x;
        game->player->ray.yo = -map_s;
        game->player->ray.xo = -game->player->ray.yo * a_tan;
    }
    else if (game->player->ray.ra < PI)
    {
        game->player->ray.ry = (((int)game->player->position.y / map_s) * map_s) + map_s;
        game->player->ray.rx = (game->player->position.y - game->player->ray.ry) * a_tan + game->player->position.x;
        game->player->ray.yo = map_s;
        game->player->ray.xo = -game->player->ray.yo * a_tan;
    }
    else
    {
        game->player->ray.ry = game->player->position.y;
        game->player->ray.rx = game->player->position.x;
        game->player->ray.dof = 8;
    }
    horizontal2(game);
}

void    horizontal2(t_game *game)
{
	int		map_s = game->map_info->height * game->map_info->width;
	
    while (game->player->ray.dof < 8)
    {
        game->player->ray.mx = (int)(game->player->ray.rx) / map_s;
        game->player->ray.my = (int)(game->player->ray.ry) / map_s;
		printf("%d %d %f %f\n", game->player->ray.mx, game->player->ray.my, game->player->ray.rx, game->player->ray.ry);
        if (game->player->ray.mx >= 0 && game->player->ray.my >= 0 && game->player->ray.mx < game->map_info->width
            && game->player->ray.my < game->map_info->height
            && game->map_info->map[game->player->ray.my][game->player->ray.mx] == '1')
			{
            	game->player->ray.dof = 8;
			}
        else
        {
			game->player->ray.rx += game->player->ray.xo;
			game->player->ray.ry += game->player->ray.yo;
			game->player->ray.dof++;
		}
    }
	draw_line(game, create_point(game->player->position.x, game->player->position.y), create_point(game->player->ray.rx, game->player->ray.ry), 0x00FF00FF);
}
