/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_call.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:08:18 by vfranco-          #+#    #+#             */
/*   Updated: 2022/11/23 10:58:52 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_file(t_data data, t_cmd ***cmds, int mode)
{
	t_file	*lst;

	if (mode == O_REDIR)
		lst = (*(*cmds))->outfiles;
	else
		lst = (*(*cmds))->infiles;
	while (lst)
	{
		tilde_expansion(data, &lst->name);
		env_var_expansion(data, &lst->name);
		lst = lst->next;
	}
}

void	expand_args(t_data data, t_cmd ***cmds)
{
	char	**args;
	int		i;

	args = (*(*cmds))->args;
	i = 0;
	while (args[i])
	{
		tilde_expansion(data, &args[i]);
		env_var_expansion(data, &args[i]);
		i++;
	}
}

void	expansions(t_data data, t_cmd **cmds)
{
	expand_file(data, &cmds, O_REDIR);
	expand_file(data, &cmds, I_REDIR);
	expand_args(data, &cmds);
}

// it is missing the expansion of the exec_cmd