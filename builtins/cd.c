/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:13:38 by asoler            #+#    #+#             */
/*   Updated: 2022/12/31 04:37:15 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verify_cd_args(char **args, int message)
{
	if (!message)
		g_exit_code = print_cmd_error(args[1], message);
	if (free_and_count_array(args, 0) > 2)
		g_exit_code = print_cmd_error(args[0], message);
	return (g_exit_code);
}

int	cd_error_treat(char **args)
{
	if (free_and_count_array(args, 0) > 2)
			g_exit_code = verify_cd_args(args, 3);
	else if (args[1])
	{
		if (chdir(args[1]))
			g_exit_code = verify_cd_args(args, 0);
	}
	return (0);
}

void	refresh_vars(t_data *data, char *old_pwd)
{
	char	*join_pwd_path;
	char	*current_path;

	current_path = getcwd(0, 0);
	join_pwd_path = ft_strjoin("PWD=", current_path);
	builtin_export(data, join_pwd_path, 0);
	builtin_export(data, old_pwd, 0);
	free(join_pwd_path);
	free(current_path);
}

void	builtin_cd(t_data *data, char *path, t_cmd *node)
{
	char	*old_pwd;
	char	*current_path;

	if (verify_cd_args(node->args, 3))
		return ;
	current_path = getcwd(0, 0);
	old_pwd = ft_strjoin("OLDPWD=", current_path);
	free(current_path);
	if (!path)
		path = get_env_var(data, "HOME")->value;
	if (chdir(path))
		verify_cd_args(node->args, 0);
	else
		refresh_vars(data, old_pwd);
	free(old_pwd);
}
