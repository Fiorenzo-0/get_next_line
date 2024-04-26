/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbruschi <lbruschi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:40:58 by lbruschi          #+#    #+#             */
/*   Updated: 2024/04/24 17:49:44 by lbruschi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*free_if(char **s1, char **s2)
{
	if (s1 && *s1)
	{
		free(*s1);
		*s1 = NULL;
	}
	if (s2 && *s2)
	{
		free(*s2);
		*s2 = NULL;
	}
	return (NULL);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_newstrjoin(char *old_str, char *buffer)
{
	char	*res;
	ssize_t	i;
	ssize_t	j;

	if (!old_str)
	{
		old_str = (char *)malloc(1 * sizeof(char));
		if (!old_str)
			return (free_if(&buffer, NULL));
		old_str[0] = '\0';
	}
	res = (char *)malloc(ft_strlen(old_str) + ft_strlen(buffer) + 1);
	if (!res)
		return (free_if(&old_str, &buffer));
	i = -1;
	j = 0;
	while (old_str[++i] != '\0')
		res[i] = old_str[i];
	while (buffer[j] != '\0')
		res[i++] = buffer[j++];
	res[ft_strlen(old_str) + ft_strlen(buffer)] = '\0';
	free_if(&old_str, NULL);
	return (res);
}

char	*ft_extract_firstline(char *old_str)
{
	char	*firstline;
	int		i;

	i = 0;
	if (!old_str[i])
		return (NULL);
	while (old_str[i] && old_str[i] != '\n')
		i++;
	firstline = malloc(sizeof(char) * (i + 2));
	if (!firstline)
		return (free_if(&old_str, NULL));
	i = 0;
	while (old_str[i] && old_str[i] != '\n')
	{
		firstline[i] = old_str[i];
		i++;
	}
	if (old_str[i] == '\n')
	{
		firstline[i] = old_str[i];
		i++;
	}
	firstline[i] = '\0';
	return (firstline);
}

char	*ft_extract_remaining_line(char *old_str)
{
	char	*remaining_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!old_str)
		return (NULL);
	while (old_str[i] && old_str[i] != '\n')
		i++;
	remaining_line = malloc(sizeof(char) * (ft_strlen(old_str) - i + 1));
	if (!remaining_line)
		return (free_if(&old_str, NULL));
	if (old_str[i])
		i++;
	while (old_str[i])
		remaining_line[j++] = old_str[i++];
	remaining_line[j] = '\0';
	free_if(&old_str, NULL);
	return (remaining_line);
}
