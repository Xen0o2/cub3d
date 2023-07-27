/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:40:36 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/28 00:34:40 by alecoutr         ###   ########.fr       */
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

void	draw_player(t_game *game)
{
	float	offset;
	float	y;
	float	x;

	offset = 4;
	y = game->player->position.y - offset - 1;
	
	while (++y < game->player->position.y + offset)
	{
		x = game->player->position.x - offset - 1;
		while (++x < game->player->position.x + offset)
			if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
				mlx_put_pixel(game->mlx_img, x, y, 0xFFFF00FF);	
	}
				
}
void	draw_map_2d(t_game *game);

void	hook_move(mlx_key_data_t keydata, void* param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_A)
		game->player->position.x -= 5;	
	if (keydata.key == MLX_KEY_D)
		game->player->position.x += 5;	
	if (keydata.key == MLX_KEY_W)
		game->player->position.y -= 5;	
	if (keydata.key == MLX_KEY_S)
		game->player->position.y += 5;
	mlx_delete_image(game->mlx, game->mlx_img);
	game->mlx_img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	draw_map_2d(game);
	draw_player(game);
	mlx_image_to_window(game->mlx, game->mlx_img, 0, 0);
}

void	draw_line(t_game *game, t_point begin, t_point end, int color)
{
	int		pixels;
	double	deltaX;
	double	deltaY;
	double	pixelX;
	double	pixelY;
	
	deltaX = end.x - begin.x;
	deltaY = end.y - begin.y;
	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = begin.x;
	pixelY = begin.y;
	while (pixels)
	{
		mlx_put_pixel(game->mlx_img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

t_point	create_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

void	draw_square(t_game *game, t_point points[4], int color)
{
	while (points[0].y != points[2].y)
	{
		draw_line(game, create_point(points[0].x, points[0].y),
			create_point(points[1].x, points[0].y), color);
		if (points[0].y < points[2].y)
			points[0].y++;
		else
			points[0].y--;
	}
}


void	draw_map_2d(t_game *game)
{
	t_point	point;
	t_point	pointo;
	t_point	points[4];
	int		color;
	int		mapS;

	point.y = 0;
	mapS = (game->map_info->height * game->map_info->width);
	while (game->map_info->map[(int)point.y])
	{
		point.x = 0;
		while (game->map_info->map[(int)point.y][(int)point.x])
		{
			if(game->map_info->map[(int)point.y][(int)point.x] == '1')
				color = 0xFFFFFFFF;
			else if(game->map_info->map[(int)point.y][(int)point.x] == '0')
				color = 0x000000FF;
			else	
			{
				point.x++;
				continue ;
			}
			pointo.x = point.x * mapS;
			pointo.y = point.y * mapS;
			points[0] = create_point(pointo.x + 1, pointo.y + 1);
			points[1] = create_point(pointo.x + mapS - 1, pointo.y + 1);
			points[2] = create_point(pointo.x + 1, pointo.y + mapS - 1);
			points[3] = create_point(pointo.x + mapS - 1, pointo.y + mapS - 1);
			draw_square(game, points, color);
			point.x++;
		}
		point.y++;
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
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d", true);
	game->mlx_img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);

	draw_map_2d(game);
	draw_player(game);
	mlx_image_to_window(game->mlx, game->mlx_img, 0, 0);
	
	mlx_loop_hook(game->mlx, &hook, game);
	mlx_key_hook(game->mlx, &hook_move, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	exit_success(game);
}
