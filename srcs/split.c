/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 16:51:24 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/22 19:45:55 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	next_word_length(char *s, char c)
{
	int	length;

	length = 0;
	while (*s && *s == c)
		s++;
	while (*s && *s != c)
	{
		s++;
		length++;
	}
	return (length);
}

int	get_sep_nbr(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s)
		{
			count++;
			while (*s != c && *s)
				s++;
		}
	}
	return (count + 1);
}

char	*create_malloc(char **tab, int length)
{
	*tab = malloc((length + 1) * sizeof(char));
	if (!*tab)
		return (NULL);
	return (*tab);
}

char	**ft_freeall(char **tab, int length)
{
	int	i;

	i = 0;
	while (i < length)
		free(tab[i++]);
	free(tab);
	return (0);
}

char	**ft_split(char *s, char c)
{
	t_split	all;

	if (!s)
		return (0);
	all.sep = get_sep_nbr(s, c);
	all.tab = malloc(all.sep * sizeof(char *));
	if (!all.tab)
		return (NULL);
	all.i = 0;
	while (all.i < all.sep - 1)
	{
		all.j = 0;
		while (*s && *s == c)
			s++;
		all.length = next_word_length(s, c);
		if (!create_malloc(&all.tab[all.i], all.length))
			return (ft_freeall(all.tab, all.i));
		while (all.j < all.length)
			all.tab[all.i][all.j++] = *s++;
		all.tab[all.i++][all.j] = 0;
	}
	all.tab[all.i] = 0;
	return (all.tab);
}
