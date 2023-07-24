/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:53:02 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/24 11:42:33 by alecoutr         ###   ########.fr       */
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

int	is_whitespace(char c)
{
	return (c == ' '
			|| c == '\n'
			|| c == '\t'
			|| c == '\v'
			|| c == '\f'
			|| c == '\r');
}

int	is_empty(char *line)
{
	while (*line)
	{
		if (!is_whitespace(*line))
			return (0);
		line++;
	}
	return (1);
}
