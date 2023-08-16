/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:40:36 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 08:25:16 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	init_game(t_game *game, int ac, char **av)
{
	init_parameters(game);
	verif_args(ac, av, game);
	parse_parameters(game);
	init_map(game);
}

void	init_window(t_game *game)
{
	game->mlx = mlx_init(game->window_width, game->window_height,
			"cub3d", true);
	mlx_set_window_limit(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, 10000, 10000);
	mlx_loop_hook(game->mlx, &hook, game);
	mlx_key_hook(game->mlx, &key_hook, game);
	mlx_resize_hook(game->mlx, &resize_hook, game);
	mlx_mouse_hook(game->mlx, &mouse_hook, game);
}

void	load_render(t_game *game)
{
	if (game->mlx_img)
		mlx_delete_image(game->mlx, game->mlx_img);
	game->mlx_img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_rays(game);
	if (game->draw_minimap)
		draw_minimap(game);
	mlx_image_to_window(game->mlx, game->mlx_img, 0, 0);
	mlx_resize_image(game->mlx_img, game->window_width, game->window_height);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		exit_error("Error\nMalloc failed\n", game);
	init_game(game, ac, av);
	init_window(game);
	load_render(game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	exit_success(game);
}
