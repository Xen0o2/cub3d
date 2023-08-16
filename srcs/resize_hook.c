/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 07:35:18 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 07:36:34 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_game	*game;
	
	game = param;
	if (height >= WINDOW_HEIGHT && width >= WINDOW_WIDTH)
	{
		game->window_height = height;
		game->window_width = width;
	}
	mlx_resize_image(game->mlx_img, game->window_width, game->window_height);
}