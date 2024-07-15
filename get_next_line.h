/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:14:52 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/15 14:59:24 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

char	*get_next_line(int fd);
int		find_newline(t_list *lst);
t_list	*find_last_node(t_list *list);
void	ft_add(t_list **lst, char *new_str);
int		len_of_line(t_list	*lst);
void	put_line(t_list *lst, char *str);

#endif