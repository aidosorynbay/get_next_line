/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:14:17 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/24 20:28:38 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strdup(const char *s1)
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
			return (result);
		}
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static char	*ft_strdup_nnl(const char *s1)
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

static void	update_buf(char **buf)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*buf)[i] != '\n' && (*buf)[i] != '\0')
		i++;
	if ((*buf)[i] == '\n')
		i++;
	temp = ft_strdup_nnl(*buf + i);
	if (temp == NULL)
	{
		free(*buf);
		*buf = NULL;
		return ;
	}
	free(*buf);
	*buf = temp;
}

static void	reader(int fd, char **buf, char **temp_buf)
{
	ssize_t	buf_count;
	char	*new_buf;

	while (!ft_strchr(*buf, '\n'))
	{
		buf_count = read(fd, *temp_buf, BUFFER_SIZE);
		if (buf_count < 1)
		{
			if (buf_count == -1)
			{
				if (*buf != NULL)
					free(*buf);
				*buf = NULL;
			}
			return (free(*temp_buf), (void)0);
		}
		(*temp_buf)[buf_count] = '\0';
		new_buf = ft_strjoin(*buf, *temp_buf);
		if (new_buf == NULL)
			return (free(*temp_buf), free(*buf), *buf = NULL, (void)0);
		free(*buf);
		*buf = new_buf;
	}
	free(*temp_buf);
}

char	*get_next_line(int fd)
{
	char			*result;
	static char		*buf;
	char			*temp_buf;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE > 2147483646
		|| BUFFER_SIZE < 1)
		return (NULL);
	if (!buf)
		buf = ft_strdup("");
	if (buf == NULL)
		return (free(buf), buf = NULL, NULL);
	temp_buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (temp_buf == NULL)
		return (free(buf), buf = NULL, NULL);
	reader(fd, &buf, &temp_buf);
	if (buf == NULL || buf[0] == '\0')
	{
		if (buf && buf[0] == '\0')
			(free(buf), buf = NULL);
		return (NULL);
	}
	result = ft_strdup(buf);
	if (result == NULL)
		return (free(buf), buf = NULL, NULL);
	return (update_buf(&buf), result);
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