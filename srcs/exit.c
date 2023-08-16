/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:29:30 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/15 19:29:45 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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