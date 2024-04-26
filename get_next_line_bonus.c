/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbruschi <lbruschi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:34:57 by lbruschi          #+#    #+#             */
/*   Updated: 2024/04/26 18:14:08 by lbruschi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if ((unsigned char)c == *str)
			return (str);
		str++;
	}
	if ((unsigned char)c == '\0')
		return (str);
	return (NULL);
}

char	*ft_read(char *old_str, int fd)
{
	char	*buffer;
	int		bytebuffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free_if(&old_str, NULL));
	bytebuffer = 1;
	while (buffer && bytebuffer > 0 && ft_strchr(old_str, '\n') == 0)
	{
		bytebuffer = read(fd, buffer, BUFFER_SIZE);
		if (bytebuffer == -1)
			return (free_if(&old_str, &buffer));
		buffer[bytebuffer] = '\0';
		old_str = ft_newstrjoin(old_str, buffer);
	}
	if (buffer)
		free_if(&buffer, NULL);
	return (old_str);
}

char	*get_next_line(int fd)
{
	static char		*old_str[OPEN_MAX];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	old_str[fd] = ft_read(old_str[fd], fd);
	if (!old_str[fd])
		return (NULL);
	line = ft_extract_firstline(old_str[fd]);
	old_str[fd] = ft_extract_remaining_line(old_str[fd]);
	if (old_str[fd] && old_str[fd][0] == '\0')
		free_if(&old_str[fd], NULL);
	return (line);
}

// int	main(void)
// {
// 	int		fd[2];
// 	int		i;
// 	char	*s1;
// 	char	*s2;

// 	i = 0;
// 	fd[0] = open("fd0", O_RDONLY);
// 	if (fd[0] == -1)
// 	{
// 		close(fd[0]);
// 		return (0);
// 	}
// 	fd[1] = open("fd1", O_RDONLY);
// 	if (fd[1] == -1)
// 	{
// 		close(fd[1]);
// 		return (0);
// 	}
// 	while (i == 0 || s1 || s2)
// 	{
// 		s1 = get_next_line(fd[0]);
// 		printf("fd0: %s\n", s1);
// 		s2 = get_next_line(fd[1]);
// 		printf("fd1: %s\n", s2);
// 		i++;
// 		if (s1)
// 		{
// 			free_if(&s1, NULL);
// 			i = 0;
// 		}
// 		if (s2)
// 		{
// 			free_if(&s2, NULL);
// 			i = 0;
// 		}
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	return (0);
// }
