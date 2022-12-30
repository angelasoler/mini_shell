/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:11:27 by asoler            #+#    #+#             */
/*   Updated: 2022/12/30 17:21:20 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_error(char *key_value)
{
	write(2, "bash: export: `", 14);
	ft_putstr_fd(key_value, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (0);
}

int	identifier_verification(char *identifier)
{
	int		i;

	i = 0;
	while (identifier[i])
	{
		if (!ft_isalnum(identifier[i]))
			return (print_error(identifier));
		i++;
	}
	return (-1);
}

int	valid_env_var(char *env)
{
	int		ret;
	char	**key_value;

	ret = 0;
	key_value = NULL;
	if (ft_strrchr(env, '='))
	{
		key_value = ft_split(env, '=');
		ret = identifier_verification(key_value[0]);
		free_and_count_array(key_value, free);
		if (ret < 0)
			ret = 1;
	}
	else
		ret = identifier_verification(env);
	return (ret);
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
	int	validate;

	if (!arg)
	{
		builtin_env(data->hash_table, 1, is_single);
		return (g_exit_code);
	}
	validate = valid_env_var(arg);
	if (!validate)
		return (1);
	else if (validate < 0)
		return (0);
	create_replace_var(data, arg);
	return (0);
}
