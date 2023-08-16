/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:47:11 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 11:12:25 by alecoutr         ###   ########.fr       */
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
