/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:53:02 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/22 21:45:02 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strrlen(char **strr)
{
	int	i;

	i = 0;
	while (strr && strr[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	int		len;

	len = 0;
	while (s1[len])
		len++;
	s2 = malloc((len + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		s2[len] = s1[len];
		len++;
	}
	s2[len] = '\0';
	return (s2);
}

int	is_empty(char *line)
{
	while (*line)
	{
		if (*line != ' '
			&& *line != '\t'
			&& *line != '\v'
			&& *line != '\f'
			&& *line != '\r')
			return (0);
		line++;
	}
	return (1);
}
