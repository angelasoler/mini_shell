/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 21:37:21 by vfranco-          #+#    #+#             */
/*   Updated: 2023/01/05 22:57:26 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#define ERROR 0
#define CONTINUE 5

static int	add_file_node(char *line, int **i, t_file **file_lst, int t)
{
	char	*word;

	while (line[(**i)] == ' ')
		(**i)++;
	word = ft_worddup(line + (**i), " <>");
	if (!word)
		return (ERROR);
	ft_file_addback(file_lst, ft_filenew(word, t));
	if (word)
		(**i) += ft_strlen(word);
	return (CONTINUE);
}

static int	build_file(char *line, int *i, t_file **file_lst, int t)
{
	if (line[(*i)] == '>' * (t == O_REDIR) + '<' * (t == I_REDIR)
		&& line[(*i + 1)]
		&& line[(*i + 1)] == '>' * (t == O_REDIR) + '<' * (t == I_REDIR))
	{
		if (!line[(*i) + 2])
			return (ERROR);
		(*i) += 2;
		return (add_file_node(line, &i, file_lst, t + 1));
	}
	else if (line[(*i)] == '>' * (t == O_REDIR) + '<' * (t == I_REDIR))
	{
		if (!line[(*i) + 1])
			return (ERROR);
		(*i)++;
		return (add_file_node(line, &i, file_lst, t));
	}
	return (1);
}

int	put_files_to_list(char *line, char **new_line, t_file **file_lst, int type)
{
	int		code;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		copy_through_quotes(line, new_line, &i, &j);
		code = build_file(line, &i, file_lst, type);
		if (code == ERROR)
			return (ERROR);
		else if (code == CONTINUE)
			continue ;
		if (!line[i])
			break ;
		(*new_line)[j++] = line[i++];
	}
	(*new_line)[j] = '\0';
	return (1);
}

t_file	*extract_files(t_cmd **cmd, int type)
{
	t_file	*file_lst;
	char	*new_line;

	new_line = malloc(ft_new_line_size((*cmd)->line, type) + 1);
	if (!new_line)
		return (ERROR);
	file_lst = NULL;
	if (put_files_to_list((*cmd)->line, &new_line, &file_lst, type) == ERROR)
	{
		free(new_line);
		return (ERROR);
	}
	free((*cmd)->line);
	(*cmd)->line = new_line;
	return (file_lst);
}

t_cmd	*get_file_structures(t_data *data)
{
	t_cmd	*cmds;
	t_cmd	*cmds_iter;

	cmds = ft_split_to_cmd_lst(data->line, '|');
	cmds_iter = cmds;
	while (cmds_iter)
	{
		cmds_iter->outfiles = extract_files(&cmds_iter, O_REDIR);
		cmds_iter->infiles = extract_files(&cmds_iter, I_REDIR);
		trim_file_names(&cmds_iter->outfiles, "\"");
		trim_file_names(&cmds_iter->infiles, "\"");
		get_cmd_attributes(&cmds_iter);
		trim_args(&cmds_iter, "\"");
		expansions(*data, &cmds_iter);
		trim_args(&cmds_iter, "\'");
		trim_file_names(&cmds_iter->outfiles, "\'");
		trim_file_names(&cmds_iter->infiles, "\'");
		cmds_iter = cmds_iter->next;
	}
	return (cmds);
}
