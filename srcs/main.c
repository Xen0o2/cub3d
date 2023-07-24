/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:40:36 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/22 21:46:18 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define GREEN 0x00FF00FF

//void	drawPlayer(mlx_image_t *mlx_img)
//{
//	mlx_put_pixel(mlx_img, px - 1, py - 1, GREEN);
//	mlx_put_pixel(mlx_img, px, py - 1, GREEN);
//	mlx_put_pixel(mlx_img, px + 1, py - 1, GREEN);
//	mlx_put_pixel(mlx_img, px - 1, py, GREEN);
//	mlx_put_pixel(mlx_img, px, py, GREEN);
//	mlx_put_pixel(mlx_img, px + 1, py, GREEN);
//	mlx_put_pixel(mlx_img, px - 1, py + 1, GREEN);
//	mlx_put_pixel(mlx_img, px, py + 1, GREEN);
//	mlx_put_pixel(mlx_img, px + 1, py + 1, GREEN);
//}

//int main(int ac, char **av)
//{
//	(void)ac;
//	(void)av;

//	mlx_t		*mlx;
//	mlx_image_t	*mlx_img;

//	mlx = mlx_init(1024, 512, "MLX42", false);
//	if (!mlx)
//		return (1);
//	mlx_img = mlx_new_image(mlx, 1024, 512);

//	px = 300; py = 300;
//	drawPlayer(mlx_img);

//	mlx_image_to_window(mlx, mlx_img, 0, 0);
//	mlx_loop(mlx);
//	mlx_terminate(mlx);
//	return (0);	
//}

void	exit_error(char *message)
{
	printf("%s", message);
	exit(1);
}

int	main(int ac, char **av)
{
	t_game	game;

	verif_args(ac, av, &game);
	init_game(&game);
	printf("%s%s%s%s%s%s",
		game.NO_TEXTURE,
		game.SO_TEXTURE,
		game.WE_TEXTURE,
		game.EA_TEXTURE,
		game.F_COLOR,
		game.C_COLOR);
	free_parameters(&game);
}
// game = parse_map(av[1]);
