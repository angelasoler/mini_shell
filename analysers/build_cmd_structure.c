/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_structure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfranco- <vfranco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 21:37:21 by vfranco-          #+#    #+#             */
/*   Updated: 2022/10/19 20:53:05 by vfranco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	copy_through_quotes(char *line, char **new_line, int *i, int *j)
{
	if (line[*i] == '\'' && ft_strchr(line + *i + 1, '\''))
	{
		(*new_line)[(*j)++] = line[(*i)++];
		while (line[*i] && line[*i] != '\'')
			(*new_line)[(*j)++] = line[(*i)++];
	}
	if (line[*i] == '\"' && ft_strchr(line + *i + 1, '\"'))
	{
		(*new_line)[(*j)++] = line[(*i)++];
		while (line[*i] && line[*i] != '\"')
			(*new_line)[(*j)++] = line[(*i)++];
	}
}

static int	build_file(char *line, int *i, t_file **file_lst, int t)
{
	char	*word;

	if (line[(*i)] == '>' * (t == REDIR) + '<' * (t == DIR) && line[(*i + 1)]
		&& line[(*i + 1)] == '>' * (t == REDIR) + '<' * (t == DIR))
	{
		if (!line[(*i) + 2])
			return (ERROR);
		word = ft_worddup(line + (*i) + 2);
		ft_file_addback(file_lst, ft_filenew(word, t + 1));
		(*i) += ft_strlen(word) + 2;
		return (CONTINUE);
	}
	else if (line[(*i)] == '>' * (t == REDIR) + '<' * (t == DIR))
	{
		if (!line[(*i) + 1])
			return (ERROR);
		word = ft_worddup(line + (*i) + 1);
		ft_file_addback(file_lst, ft_filenew(word, t));
		(*i) += ft_strlen(word) + 1;
		return (CONTINUE);
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
		return (ERROR);
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
		cmds_iter->outfiles = extract_files(&cmds_iter, REDIR);
		cmds_iter->infiles = extract_files(&cmds_iter, DIR);
		get_cmd_attributes(&cmds_iter);
		cmds_iter = cmds_iter->next;
	}
	return (cmds);
}

// accepted commands:
// cat <<eof<f1 >>'f2<3'<f4>>f5>f6 >>"f7"a '<f8' ">f9" -e| ls -la --color |ls
// cat <<eof<f1 >>'f2<3'<f4>>f5>f6 -e >>"f7"a -n -s| ls -la --color |ls
