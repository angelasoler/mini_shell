/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 15:13:38 by asoler            #+#    #+#             */
/*   Updated: 2022/12/11 15:32:15 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	builtin_cd(t_data *data, char *path)
{
	char	*join_pwd_path;
	char	*current_path;

	if (!path)
		path = get_env_var(data, "HOME")->value;
	if (chdir(path))
		print_cmd_error(path, 0);
	else
	{
		current_path = getcwd(0, 0);
		join_pwd_path = ft_strjoin("PWD=", current_path);
		builtin_export(data, join_pwd_path);
		free(join_pwd_path);
		free(current_path);
	}
}
;