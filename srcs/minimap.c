/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:46:11 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 10:46:38 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		square_size = 1;
	while (game->map_info->map[y])
	{
		x = 0;
		while (game->map_info->map[y][x])
			draw_tile(game, square_size, x++, y);
		y++;
	}
	draw_player(game);
}
