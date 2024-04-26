/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbruschi <lbruschi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:38:57 by lbruschi          #+#    #+#             */
/*   Updated: 2024/04/26 18:05:39 by lbruschi         ###   ########.fr       */
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
	static char		*old_str = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	old_str = ft_read(old_str, fd);
	if (!old_str)
		return (NULL);
	line = ft_extract_firstline(old_str);
	old_str = ft_extract_remaining_line(old_str);
	if (old_str && old_str[0] == '\0')
		free_if(&old_str, NULL);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open("fd1", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		return (0);
// 	}
// 	str = get_next_line(fd);
// 	while (str)
// 	{
// 		printf("%s", str);
// 		free(str);
// 		str = get_next_line(fd);
// 	}
// 		// str = get_next_line(fd);
// 		// printf("%s", str);
// 		// free(str);
// 		// str = get_next_line(fd);
// 		// printf("%s", str);
// 		// free(str);
// 		// str = get_next_line(fd);
// 		// printf("%s", str);
// 		// free(str);
// 	close(fd);
// 	return (0);
// }
