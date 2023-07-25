/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:53:02 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/25 10:04:49 by alecoutr         ###   ########.fr       */
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

char	**ft_strrdup(char **s1)
{
	char	**res;
	int		i;

	printf("Nouvelle longueur %d\n", ft_strrlen(s1) + 1);
	res = malloc(sizeof(char *) * (ft_strrlen(s1) + 1));
	if (!res)
		return (NULL);
	i = 0;
	printf("je renvoie sans probleme");
	while (s1[i])
	{
		res[i] = ft_strdup(s1[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
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
