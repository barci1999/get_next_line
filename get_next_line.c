/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-16 12:51:23 by pablalva          #+#    #+#             */
/*   Updated: 2024-10-16 12:51:23 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	take_the_rest(char **pre_line, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	while (pre_line[0][i] != '\0' && pre_line[0][i] != '\n')
		i++;
	if (pre_line[0][i])
		i++;
	*line = ft_substr(*pre_line, 0, i);
	if (pre_line[0][i])
	{
		temp = ft_substr(*pre_line, i, (ft_strlen(*pre_line) - i));
		free(*pre_line);
		*pre_line = temp;
	}
	else
	{
		free(*pre_line);
		*pre_line = NULL;
	}
}

char	*make_line(char *pre_line, int fd)
{
	char	*buffer;
	int		bts_read;

	bts_read = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(pre_line, '\n') && bts_read != 0)
	{
		bts_read = read(fd, buffer, BUFFER_SIZE);
		if (bts_read == 0)
			break ;
		if (bts_read == -1)
		{
			free(buffer);
			free(pre_line);
			return (NULL);
		}
		buffer[bts_read] = '\0';
		pre_line = ft_strjoin(pre_line, buffer);
		if (!pre_line)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (pre_line);
}

char	*get_next_line(int fd)
{
	static char	*pre_line = NULL;
	char		*line;

	line = NULL;
	if (fd == -1)
		return (NULL);
	pre_line = make_line(pre_line, fd);
	if (pre_line == NULL)
		return (NULL);
	take_the_rest(&pre_line, &line);
	return (line);
}

 int main()
{
	int fd;
	char *line;

	fd = open("chistes.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error abriendo el archivo");
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s",line); // Sin "\n".
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
