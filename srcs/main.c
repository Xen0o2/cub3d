/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:40:36 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/08 16:11:56 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void	exit_error(char *message, t_game *game)
{
	free_parameters(game);
	free_all(game->map_info->map);
	if (game->map_info)
		free(game->map_info);
	if (game->player)
		free(game->player);
	if (game)
		free(game);
	printf("%s", message);
	exit(1);
}

void	exit_success(t_game *game)
{
	free_parameters(game);
	free_all(game->map_info->map);
	if (game->map_info)
		free(game->map_info);
	if (game->player)
		free(game->player);
	if (game)
		free(game);
	exit(0);
}

void	hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

void	hook_move(mlx_key_data_t keydata, void* param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_A)
	{
		game->player->angle -= 0.1;
		if (game->player->angle < 0)
			game->player->angle += 2 * PI;
		game->player->delta.x = cos(game->player->angle) * 5;
		game->player->delta.y = sin(game->player->angle) * 5;
	}
	if (keydata.key == MLX_KEY_D)
	{
		game->player->angle += 0.1;
		if (game->player->angle > 2 * PI)
			game->player->angle -= 2 * PI;
		game->player->delta.x = cos(game->player->angle) * 5;
		game->player->delta.y = sin(game->player->angle) * 5;
	}
	if (keydata.key == MLX_KEY_W)
	{
		game->player->position.x += game->player->delta.x;
		game->player->position.y += game->player->delta.y;
	}
	if (keydata.key == MLX_KEY_S)
	{
		game->player->position.x -= game->player->delta.x;
		game->player->position.y -= game->player->delta.y;
	}
	mlx_delete_image(game->mlx, game->mlx_img);
	game->mlx_img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_minimap(game);
	draw_player(game);
	mlx_image_to_window(game->mlx, game->mlx_img, 0, 0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		exit_error("Error\nMalloc failed\n", game);
	init_parameters(game);
	verif_args(ac, av, game);
	parse_parameters(game);
	init_map(game);
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d", true);
	game->mlx_img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);

	draw_minimap(game);
	draw_player(game);
	mlx_image_to_window(game->mlx, game->mlx_img, 0, 0);
	
	mlx_loop_hook(game->mlx, &hook, game);
	mlx_key_hook(game->mlx, &hook_move, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	exit_success(game);
}
