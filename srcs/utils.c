/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:16:54 by alecoutr          #+#    #+#             */
/*   Updated: 2023/07/26 19:29:32 by alecoutr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*final;
	int		length;
	int		i;

	if (!s)
		return (0);
	length = ft_strlen(s);
	if (len > length)
		len = length;
	if (start >= length)
		len = 0;
	if (len > length - start)
		len = length - start;
	final = malloc((len + 1) * sizeof(char));
	if (!final)
		return (0);
	i = -1;
	while (++i < len)
		final[i] = s[i + start];
	final[i] = 0;
	return (final);
}

int	ft_strlen(char *str)
{
	int	length;

	length = 0;
	if (!str)
		return (length);
	while (str[length])
		length++;
	return (length);
}

char	*ft_strchr(char *s, char c)
{
	if (!s)
		return (0);
	while (*s)
		if (*s++ == c)
			return (s);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	t_join	all;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (0);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (0);
	all.result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!all.result)
		return (0);
	all.i = 0;
	all.x = 0;
	while (s1[all.i])
		all.result[all.x++] = s1[all.i++];
	all.i = 0;
	while (s2[all.i])
		all.result[all.x++] = s2[all.i++];
	all.result[all.x] = 0;
	free(s1);
	return (all.result);
}
