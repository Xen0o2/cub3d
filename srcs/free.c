/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:18:33 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 11:52:50 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	if (tab)
		free(tab);
}

void	free_parameters(t_game *game)
{
	if (game->NO_TEXTURE)
		mlx_delete_texture(game->NO_TEXTURE);
	if (game->SO_TEXTURE)
		mlx_delete_texture(game->SO_TEXTURE);
	if (game->WE_TEXTURE)
		mlx_delete_texture(game->WE_TEXTURE);
	if (game->EA_TEXTURE)
		mlx_delete_texture(game->EA_TEXTURE);
	if (game->NO_TEXTURE_CHAR)
		free(game->NO_TEXTURE_CHAR);
	if (game->SO_TEXTURE_CHAR)
		free(game->SO_TEXTURE_CHAR);
	if (game->WE_TEXTURE_CHAR)
		free(game->WE_TEXTURE_CHAR);
	if (game->EA_TEXTURE_CHAR)
		free(game->EA_TEXTURE_CHAR);
	if (game->F_COLOR_CHAR)
		free(game->F_COLOR_CHAR);
	if (game->C_COLOR_CHAR)
		free(game->C_COLOR_CHAR);
}
