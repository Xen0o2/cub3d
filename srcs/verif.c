/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:40:34 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 11:35:57 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	verif_args(int ac, char **av, t_game *game)
{
	char	*extension;
	int		fd;

	if (ac != 2)
		exit_error("Error\nUsage: ./cub3d <map.cub>\n", game);
	extension = ft_substr(av[1], ft_strlen(av[1]) - 4, 4);
	if (ft_strcmp(extension, ".cub"))
	{
		free(extension);
		exit_error("Error\nUsage: ./cub3d <map.cub>\n", game);
	}
	free(extension);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_error("Error\nCan't open map file\n", game);
	else
		game->fd = fd;
}

void	verif_parameters(t_game *game)
{	
	game->F_COLOR = verif_color(game, game->F_COLOR_CHAR);
	game->C_COLOR = verif_color(game, game->C_COLOR_CHAR);
	game->NO_TEXTURE = verif_texture(game, game->NO_TEXTURE_CHAR);
	game->SO_TEXTURE = verif_texture(game, game->SO_TEXTURE_CHAR);
	game->WE_TEXTURE = verif_texture(game, game->WE_TEXTURE_CHAR);
	game->EA_TEXTURE = verif_texture(game, game->EA_TEXTURE_CHAR);
}

void	verif_color_value(t_game *game, char **rgb_tab, char *rgb, int *values)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!is_digit(rgb_tab[i]))
			(void)0, free(rgb), free_all(rgb_tab),
				exit_error("Error\nInvalid color parameter\n", game);
		values[i] = ft_atoi(rgb_tab[i]);
		if (values[i] < 0 || values[i] > 255)
			(void)0, free(rgb), free_all(rgb_tab),
				exit_error("Error\nInvalid color parameter\n", game);
		i++;
	}
}

unsigned long	verif_color(t_game *game, char *color)
{
	int				*values;
	char			*rgb;
	char			**rgb_tab;
	unsigned long	value;

	values = malloc(3 * sizeof(int));
	if (!values)
		exit_error("Error\nMalloc failed during parsing\n", game);
	rgb = ft_substr(color, 2, ft_strlen(color) - 2);
	if (!rgb)
		exit_error("Error\nMalloc failed during parsing\n", game);
	rgb_tab = ft_split(color, ',');
	if (!rgb_tab)
		(void)0, free(rgb),
			exit_error("Error\nMalloc failed during parsing\n", game);
	if (ft_strrlen(rgb_tab) != 3)
		(void)0, free(rgb), free_all(rgb_tab),
			exit_error("Error\nInvalid color parameter\n", game);
	verif_color_value(game, rgb_tab, rgb, values);
	value = create_rgba(values[0], values[1], values[2], 255);
	free(values);
	free(rgb);
	free_all(rgb_tab);
	return (value);
}

mlx_texture_t	*verif_texture(t_game *game, char *texture_path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(texture_path);
	if (!texture)
		exit_error("Error\nInvalid texture path\n", game);
	return (texture);
}
