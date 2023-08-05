/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:11:17 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/04 07:03:02 by alecoutr         ###   ########.fr       */
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