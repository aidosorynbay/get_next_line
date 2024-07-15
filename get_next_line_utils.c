/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:16:17 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/15 15:03:57 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_newline(t_list *lst)
{
	int	i;
	while (lst)
	{
		i = 0;
		while (lst->str[i] && i < BUFFER_SIZE)
		{
			if (lst->str[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

t_list	*find_last_node(t_list *list)
{
	if (NULL == list)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	ft_add(t_list **lst, char *new_str)
{
	t_list	*last;
	t_list	*new;
	
	new = malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		new->str = new_str;
		new->next = NULL;
		*lst = new;
	}
	else
	{
		last = find_last_node(*lst);
		last->next = new;
		new->str = new_str;
		new->next = NULL;
	}
}

int	len_of_line(t_list	*lst)
{
	int	count;
	int	i;
	
	count = 0;
	while (lst)
	{
		i = 0;
		while (lst->str[i] != '\0' && lst->str[i] != '\n')
		{
			i++;
			count++;
			if (lst->str[i] == '\n')
				return (count + 1);
		}
		lst = lst->next;
	}
	return (count);
}

void	put_line(t_list *lst, char *str)
{
	int	i;
	int	j;
	
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->str[i] != '\0' && lst->str[i] != '\n')
		{
			str[j] = lst->str[i];
			i++;
			j++;
		}
		lst = lst->next;
	}
	str[j] = '\n';
}