/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:14:53 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/04 15:54:55 by alecoutr         ###   ########.fr       */
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
		if (pixelX >= 0 && pixelX < WINDOW_WIDTH && pixelY >= 0 && pixelY < WINDOW_HEIGHT)
			mlx_put_pixel(game->mlx_img, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
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
