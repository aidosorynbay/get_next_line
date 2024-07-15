/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:14:17 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/15 22:32:32 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	i = 0;
	if (result == NULL)
	{
		return (NULL);
	}
	while (s1[i] != '\0' && s1[i] != '\n')
	{
		result[i] = s1[i];
		i++;
	}
    if (s1[i] == '\n')
        result[i++] = '\n';
	result[i] = '\0';
	return (result);
}

void    update_buf(char *buf, int *buf_size)
{
    int     i;
	int		j;
    
    i = 0;
	j = 0;
    while ((buf)[i] != '\n' && (buf)[i] != '\0')
        i++;
    if ((buf)[i] == '\n')
        i++;
    while (buf[i])
		buf[j++] = buf[i++];
	buf[j] = '\0';
	*buf_size = j;
}

void    reader(int fd, char *buf, int *buf_size)
{
    int     buf_count;
    char    temp_buf[BUFFER_SIZE + 1];

    while (ft_strchr(buf, '\n') == NULL)
    {
		buf_count = read(fd, temp_buf, BUFFER_SIZE);
		if (buf_count <= 0)
			return ;
		temp_buf[buf_count] = '\0';
        ft_strlcat(buf, temp_buf, *buf_size + buf_count + 1);
        *buf_size += buf_count;
    }
}

char *get_next_line(int fd)
{
	char            *result;
    static char     buf[BUFFER_SIZE + 1];
    static int      buf_size;

    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
        return NULL;
    reader(fd, buf, &buf_size);
    if (buf_size == 0)
        return NULL;
    result = ft_strdup(buf);
    update_buf(buf, &buf_size);
    return (result);
}

int	main(void)
{
	int fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }

    char *line = get_next_line(fd);
    while (line)
    {
        printf("|%s|\n", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return 0;
}
