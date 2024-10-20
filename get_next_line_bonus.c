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

#include "get_next_line_bonus.h"

static void	take_the_rest(char **pre_line, char **line)
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

static char	*make_line(char *pre_line, int fd)
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
	static char	*pre_line[MAX_FD];
	char		*line;

	line = NULL;
	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	pre_line[fd] = make_line(pre_line[fd], fd);
	if (pre_line[fd] == NULL)
		return (NULL);
	take_the_rest(&pre_line[fd], &line);
	return (line);
}

/*int	main(void)
{
	int	fd1 = open("archivo1.txt", O_RDONLY);
	int	fd2 = open("archivo2.txt", O_RDONLY);
	int	fd3 = open("archivo3.txt", O_RDONLY);

	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
	{
		printf("Error al abrir uno de los archivos.\n");
		return (1);
	}
	char	*line1;
	char	*line2;
	char	*line3;
	int		line_number = 1;

	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);

		if (!line1 && !line2 && !line3)
			break;
		if (line1)
		{
			printf("Archivo 1, línea %d: %s", line_number, line1);
			free(line1);
		}
		if (line2)
		{
			printf("Archivo 2, línea %d: %s", line_number, line2);
			free(line2);
		}
		if (line3)
		{
			printf("Archivo 3, línea %d: %s", line_number, line3);
			free(line3);
		}

		line_number++;  
	}

	close(fd1);
	close(fd2);
	close(fd3);

	return (0);
}*/
