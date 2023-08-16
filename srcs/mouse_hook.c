/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 07:36:56 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 11:12:13 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mouse_hook(mouse_key_t button,
	action_t action,
	modifier_key_t mods,
	void *param)
{
	t_game	*game;

	game = param;
	(void)button;
	(void)action;
	(void)mods;
	if (action)
	{
		if (game->player->in_game)
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
		else
		{
			mlx_set_mouse_pos(game->mlx,
				game->window_width / 2,
				game->window_height / 2);
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
		}
		game->player->in_game = !game->player->in_game;
	}
}
