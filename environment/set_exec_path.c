/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exec_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:43:42 by vfranco-          #+#    #+#             */
/*   Updated: 2023/01/22 05:07:19 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_env_lst(t_env *lst)
{
	t_env	*aux;
	int		count;

	count = 0;
	aux = lst;
	while (aux)
	{
		count++;
		aux = aux->next;
	}
	return (count);
}

int	count_env_var(t_env **hash_table)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < TABLE_SIZE)
	{
		if (hash_table[i])
			count += count_env_lst(hash_table[i]);
		i++;
	}
	return (count);
}

void	alloc_envp(t_data *data, t_env *env)
{
	char	*key;
	int		i;
	t_env	*aux;

	aux = env;
	i = 0;
	while (data->envp[i])
		i++;
	while (aux)
	{
		if (aux->value)
		{
			key = ft_strjoin(aux->key, "=");
			data->envp[i] = ft_strjoin(key, aux->value);
			free(key);
		}
		else
			data->envp[i] = ft_strdup(aux->key);
		aux = aux->next;
		i++;
	}
}

void	set_envp(t_data *data)
{
	int	count;
	int	i;

	count = count_env_var(data->hash_table);
	i = 0;
	data->envp = calloc(sizeof(char *), count + 1);
	while (i < TABLE_SIZE)
	{
		if (data->hash_table[i])
			alloc_envp(data, data->hash_table[i]);
		i++;
	}
}

void	set_exec_paths(t_data *data)
{
	t_env	*node;
	char	**paths;
	int		lines;
	int		i;

	node = get_env_var(data, "PATH");
	if (!node)
	{
		data->path = NULL;
		return ;
	}
	paths = ft_split(node->value, ':');
	lines = free_and_count_array(paths, 0) + 1;
	data->path = malloc(lines * sizeof(char *));
	i = 0;
	while (paths[i])
	{
		data->path[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	data->path[i] = 0;
	free_and_count_array(paths, free);
}
