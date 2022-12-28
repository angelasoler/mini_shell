/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:11:27 by asoler            #+#    #+#             */
/*   Updated: 2022/12/28 19:30:27 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_error(char *env)
{
	write(2, "bash: export: `", 14);
	ft_putstr_fd(env, 2);
	ft_putendl_fd("': No such file or directory", 2);
	return (-1);
}

int	valid_env_var(char *env)
{
	char	**key_value;
	int		i;

	i = 1;
	key_value = NULL;
	if (ft_isdigit(*env) || !ft_isalpha(*env))
		return (print_error(env));
	if (!ft_strrchr(env, '='))
	{
		key_value = ft_split(env, '=');
		while (key_value[0][i])
		{
			if (!ft_isalnum(key_value[0][i]))
			{
				free_and_count_array(key_value, free);
				return (print_error(env));
			}
			i++;
		}
		free_and_count_array(key_value, free);
	}
	return (1);
}

void	create_replace_var(t_data *data, char *arg)
{
	unsigned int	i;
	t_env			*node;
	char			**key_value;

	key_value = ft_split(arg, '=');
	node = get_env_var(data, key_value[0]);
	if (!node)
	{
		i = hash(key_value[0]);
		node = ft_envnew(key_value[0], key_value[1]);
		ft_env_addback(&data->hash_table[i], node);
	}
	else
	{
		free(node->value);
		node->value = ft_strdup(key_value[1]);
	}
	free_and_count_array(key_value, free);
}

int	builtin_export(t_data *data, char *arg, int is_single)
{
	if (!arg)
	{
		builtin_env(data->hash_table, 1, is_single);
		return (0);
	}
	if (valid_env_var(arg) < 0)
		return (1);
	create_replace_var(data, arg);
	return (0);
}
