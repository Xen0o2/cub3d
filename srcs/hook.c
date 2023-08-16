/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 07:32:15 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 12:04:52 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_mouse(t_game *game)
{
	float	difference;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (game->player->in_game)
	{
		mlx_get_mouse_pos(game->mlx, &x, &y);
		difference = x - game->window_width / 2;
		game->player->angle += difference * 1.5 / (game->window_width / 2);
		mlx_set_mouse_pos(game->mlx, game->window_width / 2,
			game->window_height / 2);
		if (game->player->angle < 0)
			game->player->angle += 2 * PI;
		game->player->delta.x = cos(game->player->angle) * game->player->speed;
		game->player->delta.y = sin(game->player->angle) * game->player->speed;
		load_render(game);
	}
}

void	hook(void *param)
{
	t_game	*game;

	game = param;
	rotate_mouse(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}
