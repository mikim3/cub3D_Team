/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:39:13 by soylee            #+#    #+#             */
/*   Updated: 2022/08/27 18:42:47 by soylee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	*free_gnl(char *s)
{
	free(s);
	return (NULL);
}

static char	*split_line_rest(char **line)
{
	char	*nl;
	char	*rest;
	char	*tmp;
	size_t	len;

	nl = ft_strchr(*line, '\n');
	if (!nl || *(nl + 1) == 0)
		return (NULL);
	rest = ft_strdup(nl + 1);
	len = (size_t)(nl - *line) + 1;
	tmp = *line;
	*line = ft_substr(tmp, 0, len);
	tmp = free_gnl(tmp);
	return (rest);
}

static char	*read_file(int fd, char *line)
{
	char		*buf;
	ssize_t		cnt;
	char		*tmp;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
	{
		line = free_gnl(line);
		return (NULL);
	}
	while (!ft_strchr(line, '\n'))
	{
		cnt = read(fd, buf, BUFFER_SIZE);
		if (cnt <= 0)
			break ;
		buf[cnt] = '\0';
		tmp = ft_strjoin(line, buf);
		line = free_gnl(line);
		line = tmp;
		tmp = NULL;
	}
	buf = free_gnl(buf);
	if (cnt < 0 || *line == 0)
		line = free_gnl(line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rest)
		rest = ft_strdup("");
	line = ft_strdup(rest);
	rest = free_gnl(rest);
	line = read_file(fd, line);
	if (!line)
		return (NULL);
	rest = split_line_rest(&line);
	return (line);
}
