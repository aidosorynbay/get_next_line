/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:16:17 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/15 22:32:26 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (str + i);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0' && s[count] != '\n')
		count++;
	if (s[count] == '\n')
		count++;
	return (count);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
    size_t j;

    i = 0;
    while (dst[i] != '\0' && i < dstsize)
        i++;
    j = i;
    while (src[i - j] != '\0' && i + 1 < dstsize)
    {
        dst[i] = src[i - j];
        i++;
    }
    if (j < dstsize)
        dst[i] = '\0';
    return (j + ft_strlen(src));
}
