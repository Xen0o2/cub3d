/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:11:17 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/08 13:46:05 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float   deg_to_rad(float degree)
{   
    return (degree * ( M_PI / 180.0 ));
}

float ft_abs(int value)
{
    if (value < 0)
        return (-value);
    return (value);
}

float   distance(t_point p1, t_point p2)
{
    return ( sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)) );
}
