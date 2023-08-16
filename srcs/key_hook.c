/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:32:49 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 16:14:05 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	collision(t_game *game)
{
	game->player->r.ixo = 0;
	if (game->player->delta.x < 0)
		game->player->r.ixo = -20;
	else
		game->player->r.ixo = 20;
	game->player->r.iyo = 0;
	if (game->player->delta.y < 0)
		game->player->r.iyo = -20;
	else
		game->player->r.iyo = 20;
	game->player->r.ipx = game->player->position.x / 64;
	game->player->r.ipx_add_ixo
		= (game->player->position.x + game->player->r.ixo) / 64;
	game->player->r.ipx_sub_ixo
		= (game->player->position.x - game->player->r.ixo) / 64;
	game->player->r.ipy = game->player->position.y / 64;
	game->player->r.ipy_add_iyo
		= (game->player->position.y + game->player->r.iyo) / 64;
	game->player->r.ipy_sub_iyo
		= (game->player->position.y - game->player->r.iyo) / 64;
}

void	rotate_key(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_A)
	{
		game->player->angle -= 0.1;
		if (game->player->angle < 0)
			game->player->angle += 2 * PI;
		game->player->delta.x = cos(game->player->angle) * 5;
		game->player->delta.x = sin(game->player->angle) * 5;
	}
	if (keydata.key == MLX_KEY_D)
	{
		game->player->angle += 0.1;
		if (game->player->angle > 2 * PI)
			game->player->angle -= 2 * PI;
		game->player->delta.x = cos(game->player->angle) * 5;
		game->player->delta.x = sin(game->player->angle) * 5;
	}
}

void	move_key(t_game *game, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_W)
	{
		if (game->map_info->map[game->player->r.ipy]
			[game->player->r.ipx_add_ixo] != '1')
			game->player->position.x += game->player->delta.x;
		if (game->map_info->map[game->player->r.ipy_add_iyo]
			[game->player->r.ipx] != '1')
			game->player->position.y += game->player->delta.y;
	}
	if (keydata.key == MLX_KEY_S)
	{
		if (game->map_info->map[game->player->r.ipy]
			[game->player->r.ipx_sub_ixo] != '1')
			game->player->position.x -= game->player->delta.x;
		if (game->map_info->map[game->player->r.ipy_sub_iyo]
			[game->player->r.ipx] != '1')
			game->player->position.y -= game->player->delta.y;
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	collision(game);
	rotate_key(game, keydata);
	move_key(game, keydata);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		game->draw_minimap = !game->draw_minimap;
	if (keydata.key == MLX_KEY_LEFT_SHIFT)
	{
		if (game->player->speed == 5)
			game->player->speed = 20;
		else
			game->player->speed = 5;
	}
	mlx_delete_image(game->mlx, game->mlx_img);
	game->mlx_img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_walls(game);
	if (game->draw_minimap)
		draw_minimap(game);
	mlx_image_to_window(game->mlx, game->mlx_img, 0, 0);
	mlx_resize_image(game->mlx_img, game->window_width, game->window_height);
}
