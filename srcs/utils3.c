/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:11:17 by alecoutr          #+#    #+#             */
/*   Updated: 2023/08/16 11:14:58 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	deg_to_rad(float degree)
{
	return (degree * (M_PI / 180.0));
}

float	ft_abs(int value)
{
	if (value < 0)
		return (-value);
	return (value);
}

float	distance(t_point p1, t_point p2)
{
	return (sqrt((p2.x - p1.x) * (p2.x - p1.x)
			+ (p2.y - p1.y) * (p2.y - p1.y)));
}

int	is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

long long int	ft_atoi(const char *s)
{
	long long int	result;
	int				sign;

	result = 0;
	sign = 1;
	while ((*s == ' ' || *s == '\r' || *s == '\t')
		|| (*s == '\n' || *s == '\v' || *s == '\f'))
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	while (*s >= '0' && *s <= '9')
		result = result * 10 + (*s++ - '0');
	return (result * sign);
}
