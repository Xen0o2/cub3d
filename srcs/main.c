/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:40:36 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/26 11:22:21 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(char *message, t_game *game)
{
	free_parameters(game);
	if (game->map_info)
		free(game->map_info);
	if (game)
		free(game);
	printf("%s", message);
	exit(1);
}

void	hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
}

void	draw_player(t_game *game)
{
	float	offset;
	float	y;
	float	x;

	offset = 4;
	y = game->player->py - offset - 1;
	
	while (++y < game->player->py + offset)
	{
		x = game->player->px - offset - 1;
		while (++x < game->player->px + offset)
			if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
				mlx_put_pixel(game->mlx_img, x, y, 0xffffff);	

	}
	mlx_image_to_window(game->mlx, game->mlx_img, 0, 0);
}

void	hook_move(mlx_key_data_t keydata, void* param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_A)
		game->player->px -= 5;	
	if (keydata.key == MLX_KEY_D)
		game->player->px += 5;	
	if (keydata.key == MLX_KEY_W)
		game->player->py -= 5;	
	if (keydata.key == MLX_KEY_S)
		game->player->py += 5;
	mlx_delete_image(game->mlx, game->mlx_img);
	game->mlx_img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_player(game);
}

void	draw_line(t_game *game, t_point begin, t_point end)
{
	double	deltaX = end.x - begin.x;
	double	deltaY = end.y - begin.y;

	// https://gontjarow.github.io/MiniLibX/mlx-tutorial-draw-line.html
}

void	draw_map_2d(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map_info->map[y])
	{
		x = 0;
		while (game->map_info->map[x])
		{
			
		}
	}
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		exit_error("Error\nMalloc failed\n", game);
	verif_args(ac, av, game);
	init_parameters(game);
	init_map(game);
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d", false);
	game->mlx_img= mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);

	draw_player(game);
	
	mlx_loop_hook(game->mlx, &hook, game);
	mlx_key_hook(game->mlx, &hook_move, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);

	free_parameters(game);
	free_all(game->map_info->map);
	free(game->map_info);
	free(game->player);
	free(game);
}
