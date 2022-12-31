/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:11:27 by asoler            #+#    #+#             */
/*   Updated: 2022/12/31 06:34:11 by asoler           ###   ########.fr       */
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
	if (!ft_isalpha(*identifier))
		return (print_error(identifier));
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
	if (ft_strlen(env) == 1 && !identifier_verification(env))
		return (0);
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

int	builtin_export(t_data *data, char **args, int is_single)
{
	int	validate;
	int	i;

	i = 1;
	if (!args[i])
	{
		builtin_env(data->hash_table, 1, is_single);
		return (g_exit_code);
	}
	while (args[i])
	{
		validate = valid_env_var(args[i]);
		if (validate == 1)
		{
			create_replace_var(data, args[i]);
		}
		i++;
	}
	if (!validate)
		return (1);
	return (0);
}
