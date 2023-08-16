/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:14:53 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 10:51:22 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	create_point(float x, float y)
{
	t_point	point;

	point.x = (int)x;
	point.y = (int)y;
	return (point);
}

void	draw_line(t_game *game, t_point begin, t_point end, int color)
{
	int		pixels;
	t_point	delta;
	t_point	pixel;

	delta.x = end.x - begin.x;
	delta.y = end.y - begin.y;
	pixels = sqrt((delta.x * delta.x) + (delta.y * delta.y));
	delta.x /= pixels;
	delta.y /= pixels;
	pixel.x = begin.x;
	pixel.y = begin.y;
	while (pixels)
	{
		if (pixel.x >= 0 && pixel.x < game->window_width
			&& pixel.y >= 0 && pixel.y < game->window_height)
			mlx_put_pixel(game->mlx_img, pixel.x, pixel.y, color);
		pixel.x += delta.x;
		pixel.y += delta.y;
		--pixels;
	}
}

void	draw_square(t_game *game, t_point points[2], int color)
{
	while (points[0].y != points[1].y)
	{
		draw_line(game, create_point(points[0].x, points[0].y),
			create_point(points[1].x, points[0].y), color);
		if (points[0].y < points[1].y)
			points[0].y++;
		else
			points[0].y--;
	}
}
