/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:14:17 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/15 15:03:26 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	create_list(t_list **lst, int fd)
{
	int		buf_count;
	char	*buf;
	
	while (!(find_newline(*lst)))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		buf_count = read(fd, buf, BUFFER_SIZE);
		if (!buf_count)
		{
			free(buf);
			return ;
		}
		buf[buf_count] = '\0';
		ft_add(lst, buf);
	}
}

char	*get_line(t_list *list)
{
	int	str_len;
	char	*str;

	str_len = len_of_line(list);
	str = malloc(sizeof(char) * (str_len + 1));
	if (str == NULL)
		return NULL;
	put_line(list, str);
	return str;
}

char	*get_next_line(int fd)
{
	t_list	*list;
	char	*result;

	list = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &result, 0) < 0)
		return NULL;
	create_list(&list, fd);
	if (list == NULL)
		return NULL;
	result = get_line(list);
	return (result);
}

int	main(void)
{
	int	fd;
	fd = open("test.txt", O_RDONLY);
	printf("|%s|\n", get_next_line(fd));
}