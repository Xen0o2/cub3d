/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:40:36 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/22 17:16:13 by alecoutr         ###   ########.fr       */
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

void	verif_args(int ac, char **av, t_game *game)
{
	char	*extension;
	int		fd;

	if (ac != 2)
		exit_error("Error\nUsage: ./cub3d <map.cub>\n");
	extension = ft_substr(av[1], ft_strlen(av[1]) - 4, 4);
	if (ft_strcmp(extension, ".cub"))
	{
		free(extension);
		exit_error("Error\nUsage: ./cub3d <map.cub>\n");
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_error("Error\nCan't open map file\n");
	else
		game->fd = fd;
}



t_game	parse_map(char *path)
{
	t_game	game;
	
	game.fd = ft_open(path);
	game.map_info.width = 0;
	game.map_info.height = get_height(&game);
	game.fd = ft_open(path);
	getMap(&game);
	return (game);
}

int	is_empty(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\v' && *line != '\f' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

void	parse_args(t_game *game)
{
	char	*line;
	char	**infos;
	int		count;

	line = get_next_line(game->fd);
	count = 0;
	while (line)
	{
		if (is_empty(line))
			continue;
		infos = ft_split(line, ' ');
		if (ft_strrlen(infos) == 2)
		{
			if (!ft_strcmp(infos[0], "NO"))
				(void)0,game->NO_TEXTURE = infos[1], count++;
			else if (!ft_strcmp(infos[0], "SO"))
				(void)0,game->SO_TEXTURE = infos[1], count++;
			else if (!ft_strcmp(infos[0], "WE"))
				(void)0,game->WE_TEXTURE = infos[1], count++;
			else if (!ft_strcmp(infos[0], "EA"))
				(void)0,game->EA_TEXTURE = infos[1], count++;
			else if (!ft_strcmp(infos[0], "F"))
				(void)0,game->F_COLOR = infos[1], count++;
			else if (!ft_strcmp(infos[0], "C"))
				(void)0,game->C_COLOR = infos[1], count++;
		}

		if (count == 6)
			break ;		
	}
	printf("F")
}

int main(int ac, char **av)
{
	t_game game;
	
	verif_args(ac, av, &game);
	parse_args(&game);
	game = parse_map(av[1]);
}
























