/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_call.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:08:18 by vfranco-          #+#    #+#             */
/*   Updated: 2023/01/22 05:18:32 by asoler           ###   ########.fr       */
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
		if (lst->name)
		{
			tilde_expansion(data, &lst->name);
			env_var_expansion(data, &lst->name);
		}
		lst = lst->next;
	}
}

int	verify_realloc_args(char ***args, int position)
{
	char	**aux;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	aux = *args;
	size = free_and_count_array(aux, 0);
	while (j < size)
	{
		if (j > position)
		{
			free(aux[i]);
			aux[i] = ft_strdup(aux[j]);
		}
		if (j != position)
			i++;
		j++;
	}
	free(aux[j - 1]);
	aux[j - 1] = 0;
	return (1);
}

void	expand_args(t_data data, t_cmd ***cmds)
{
	char	**args;
	int		i;

	args = (*(*cmds))->args;
	i = 0;
	while (args[i])
	{
		if (ft_strlen(args[i]) < 2)
		{
			i++;
			continue ;
		}
		tilde_expansion(data, &args[i]);
		if (*args[i] == '$' && \
			*(args[i] + 1) != '?' \
			&& !get_env_var(&data, args[i] + 1))
		{
			verify_realloc_args(&args, i);
			continue ;
		}
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
