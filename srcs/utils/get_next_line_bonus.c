/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfarkas <jfarkas@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 04:51:04 by jfarkas           #+#    #+#             */
/*   Updated: 2024/03/24 21:56:33 by jfarkas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_strjoin(char const *line, char const *buff, char line_end)
{
	char	*join;
	int		line_s;
	int		buff_s;

	if (!line && !buff)
		return (NULL);
	line_s = ft_strlen(line, '\0');
	if (line_end == '\n')
		buff_s = ft_strlen(buff, '\n') + 2;
	else
		buff_s = ft_strlen(buff, '\0') + 1;
	join = malloc((line_s + buff_s) * sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_bzero(join, line_s + buff_s);
	ft_strlcat(join, line, line_s + 1);
	ft_strlcat(join, buff, line_s + buff_s);
	if (line_end == '\n')
		join[ft_strlen(join, '\0')] = '\n';
	free((char *)line);
	return (join);
}

void	get_next_buff(int fd, int *rd, char *buff)
{
	buff[BUFFER_SIZE] = '\0';
	ft_bzero(buff, ft_strlen(buff, '\0') + 1);
	*rd = read(fd, buff, BUFFER_SIZE);
}

char	*get_line(int fd, int *rd, char *buff)
{
	char	*line;

	if (!(line = malloc(sizeof(char))))
		return (NULL);
	line[0] = '\0';
	while (!ft_strchr(buff, '\n'))
	{
		if (*rd == 0 && line[0] != '\0')
		{
			ft_bzero(buff, ft_strlen(buff, '\0') + 1);
			return (line);
		}
		else if (*rd <= 0)
		{
			free(line);
			return (NULL);
		}
		line = ft_strjoin(line, buff, '\0');
		if (line == NULL)
			return (NULL);
		get_next_buff(fd, rd, buff);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	int			rd;
	static char	buff[MAX_FD][BUFFER_SIZE + 1];

	rd = 1;
	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	line = get_line(fd, &rd, buff[fd]);
	if (line == NULL)
		return (NULL);
	if (rd == 0 && line[0] != '\0')
		return (line);
	line = ft_strjoin(line, buff[fd], '\n');
	update_buff(buff[fd]);
	return (line);
}
