/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:11:27 by asoler            #+#    #+#             */
/*   Updated: 2022/12/10 21:05:14 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_env_var(char *env)
{
	if (!ft_strrchr(env, '='))
		return (0);
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

int	builtin_export(t_data *data, char *arg)
{
	if (!arg)
	{
		builtin_env(data->hash_table, 1);
		return (0);
	}
	if (!valid_env_var(arg))
		return (1);
	create_replace_var(data, arg);
	return (0);
}

// - export deve funcionar unicamente com formato key=value
		// - quando usado com pipe retorna menssagem
			// - tmbm passando numero como nome da var
			// export 1=sdfsd
			// bash: export: `1=sdfsd': not a valid identifier
			// export HH+JJ | ls
			// bash: export: `HH+JJ': not a valid identifier