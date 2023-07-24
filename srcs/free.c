/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:18:33 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/22 21:44:06 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_parameters(t_game *game)
{
	if (game->NO_TEXTURE)
		free(game->NO_TEXTURE);
	if (game->SO_TEXTURE)
		free(game->SO_TEXTURE);
	if (game->WE_TEXTURE)
		free(game->WE_TEXTURE);
	if (game->EA_TEXTURE)
		free(game->EA_TEXTURE);
	if (game->F_COLOR)
		free(game->F_COLOR);
	if (game->C_COLOR)
		free(game->C_COLOR);
}
