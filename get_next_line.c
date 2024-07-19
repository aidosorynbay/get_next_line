/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:14:17 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/19 20:51:46 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	size_t	i;

	result = malloc(sizeof(char) * (ft_strlen_nl(s1) + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '\n')
		{
			result[i++] = '\n';
			result[i] = '\0';
			return result;
		}
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strdup_nl(const char *s1)
{
	char	*result;
	size_t	i;

	result = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void    update_buf(char **buf)
{
	int     i;
	char	*temp;
	
	i = 0;
	while ((*buf)[i] != '\n' && (*buf)[i] != '\0')
		i++;
	if ((*buf)[i] == '\n')
		i++;
	temp = ft_strdup_nl(*buf + i);
	if (temp == NULL) // Check for allocation failure
	{
		free(*buf);
		*buf = NULL;
		return;
	}
	free(*buf);
	*buf = temp;
}

void	reader(int fd, char **buf)
{
	ssize_t	buf_count;
	char	temp_buf[BUFFER_SIZE + 1];
	char	*new_buf;

	while (!ft_strchr(*buf, '\n'))
	{
		buf_count = read(fd, temp_buf, BUFFER_SIZE);
		if (buf_count < 1)
		{
			if (buf_count == (-1))
			{
				if (*buf != NULL)
					free(*buf);
				*buf = NULL;
			}
			return ;
		}
		temp_buf[buf_count] = '\0';
		new_buf = ft_strjoin(*buf, temp_buf);
		if (new_buf == NULL) // Check for allocation failure
		{
			free(*buf);
			*buf = NULL;
			return;
		}
		free(*buf);
		*buf = new_buf;
	}
}

char *get_next_line(int fd)
{
	char            *result;
	static char     *buf;

	if (fd < 0 || BUFFER_SIZE < 1 || fd > 1024)
		return (NULL);
	if (!buf)
		buf = ft_strdup("");
	if (buf == NULL)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	reader(fd, &buf);
	if (buf == NULL || buf[0] == '\0')
	{
		if (buf[0] == '\0')
			free(buf);
		buf = NULL;
		return (NULL);
	}
	result = ft_strdup(buf);
	if (result == NULL) // Check for allocation failure
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	update_buf(&buf);
	return (result);
}

// int	main(void)
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("|%s|\n", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// 	// printf("|%s|\n", line);
// 	close(fd);
// 	return 0;
// }