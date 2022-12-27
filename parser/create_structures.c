/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_structures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 22:02:17 by vfranco-          #+#    #+#             */
/*   Updated: 2022/12/27 20:11:24 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_file	*ft_filenew(char *name, int type)
{
	t_file	*lst;

	lst = malloc(sizeof(t_file));
	if (!lst)
		return (NULL);
	lst->name = name;
	lst->type = type;
	lst->fd = -1;
	lst->hd_pid = -1;
	lst->next = NULL;
	return (lst);
}

void	ft_file_addback(t_file **lst, t_file *new)
{
	t_file	*p;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}

t_cmd	*ft_cmdnew(char *phrase)
{
	t_cmd	*lst;

	lst = malloc(sizeof(t_cmd));
	if (!lst)
		return (NULL);
	lst->line = phrase;
	lst->prev = NULL;
	lst->next = NULL;
	return (lst);
}

void	ft_cmd_addback(t_cmd **lst, t_cmd *new)
{
	t_cmd	*p;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		p = *lst;
		while (p->next)
			p = p->next;
		p->next = new;
		new->prev = p;
	}
}
