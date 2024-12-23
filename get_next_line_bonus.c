/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:22:03 by rmouafik          #+#    #+#             */
/*   Updated: 2024/12/12 12:21:58 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_tal_newline(int fd, char *line)
{
	char	*buffer;
	ssize_t	chars_read;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(line), line = NULL);
	chars_read = 1;
	while (!ft_strchr(line, '\n') && chars_read > 0)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read == -1)
		{
			return (free(buffer), free (line), NULL);
		}
		buffer[chars_read] = '\0';
		tmp = line;
		line = ft_strjoin(line, buffer);
		if (!line)
			return (free(buffer), buffer = NULL, free(line), line = NULL, NULL);
		free(tmp);
		tmp = NULL;
	}
	return (free(buffer), line);
}

char	*rest_after_newline(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	str = malloc(ft_strlen(line) - i + 1);
	if (!str)
		return (free(line), line = NULL, NULL);
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	free(line);
	return (str);
}

char	*extract_next_line(char *line)
{
	int		i;
	char	*str;

	i = 0;
	if (!line || !line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (free(line), NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		str[i] = line[i];
		i++;
	}
	return (str[i] = '\0', str);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	char		*next_line;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (free(line[fd]), line[fd] = NULL, NULL);
	line[fd] = read_tal_newline(fd, line[fd]);
	if (!line[fd])
		return (free(line[fd]), line[fd] = NULL, NULL);
	next_line = extract_next_line(line[fd]);
	line[fd] = rest_after_newline(line[fd]);
	return (next_line);
}
