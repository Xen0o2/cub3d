/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:40:36 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/25 10:01:13 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(char *message, t_game *game)
{
	if (game)
		free(game);
	free_parameters(game);
	printf("%s", message);
	exit(1);
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
	
	printf("parsing termine");
	printf("Hauteur %d et largeur %d\n", game->map_info->height, game->map_info->width);
	
	
	
	free_parameters(game);
}
// game = parse_map(av[1]);
