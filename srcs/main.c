/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:40:36 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/24 11:33:25 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(char *message, t_game *game)
{
	free_parameters(game);
	printf("%s", message);
	exit(1);
}

int	main(int ac, char **av)
{
	t_game	game;

	verif_args(ac, av, &game);
	init_parameters(&game);
	init_map(&game);
	
	
	
	
	free_parameters(&game);
}
// game = parse_map(av[1]);
