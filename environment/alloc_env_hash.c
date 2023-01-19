/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_env_hash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 08:00:54 by vfranco-          #+#    #+#             */
/*   Updated: 2023/01/19 13:13:52 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

unsigned int	hash(char *name)
{
	unsigned int	hash;
	int				c;

	hash = 5381;
	while (*name)
	{
		c = *name;
		hash = (((hash << 5) + hash) + c) % TABLE_SIZE;
		name++;
	}
	return (hash);
}

int	hash_table_insert(t_data *data, char *env)
{
	unsigned int	index;
	t_env			*node;
	char			**split_line;
	char			*value;

	split_line = ft_split(env, '=');
	index = hash(split_line[0]);
	value = ft_strchr(env, '=');
	node = ft_envnew(split_line[0], value + 1);
	free_and_count_array(split_line, free);
	ft_env_addback(&data->hash_table[index], node);
	return (1);
}

void	alloc_env_hash(char **envp, t_data *data)
{
	int	i;

	i = 0;
	data->hash_table = ft_calloc(sizeof(t_env *), TABLE_SIZE);
	while (envp[i])
	{
		hash_table_insert(data, envp[i]);
		i++;
	}
}
