/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:11:27 by asoler            #+#    #+#             */
/*   Updated: 2023/01/05 23:19:42 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_error(char *key_value)
{
	write(2, "bash: export: `", 14);
	ft_putstr_fd(key_value, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

int	identifier_verification(char *identifier)
{
	int		i;

	i = 0;
	if (!identifier)
		return (0);
	if (!ft_isalpha(*identifier) && *identifier != '_')
		return (print_error(identifier));
	i++;
	while (identifier[i])
	{
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
			return (print_error(identifier));
		i++;
	}
	return (0);
}

int	valid_env_var(char *env)
{
	int		ret;
	char	**key_value;

	ret = 0;
	key_value = NULL;
	if (ft_strlen(env) == 1 && identifier_verification(env))
		return (1);
	if (ft_strrchr(env, '='))
	{
		key_value = ft_split(env, '=');
		ret = identifier_verification(key_value[0]);
		free_and_count_array(key_value, free);
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
		if (!validate)
			create_replace_var(data, args[i]);
		i++;
	}
	return (validate);
}
