/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:21:51 by asoler            #+#    #+#             */
/*   Updated: 2022/12/10 21:19:21 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_var(t_env *prev, t_env *node)
{
	if (prev && node->next)
		prev->next = node->next;
	if (!node->next)
		prev->next = NULL;
	ft_envdelone(node, free);
}

int	builtin_unset(t_data *data, char *key)
{
	unsigned int	index;
	t_env			*node;
	t_env			*prev;
	int				len;

	if (!key)
		return (1);
	index = hash(key);
	node = data->hash_table[index];
	prev = NULL;
	len = ft_strlen(key);
	while (node)
	{
		if (!ft_strncmp(key, node->key, len))
		{
			remove_var(prev, node);
			break ;
		}
		prev = node;
		node = node->next;
	}
	return (0);
}
