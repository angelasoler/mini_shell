/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:08:18 by vfranco-          #+#    #+#             */
/*   Updated: 2023/01/03 15:59:24 by asoler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	tilde_expansion(t_data data, char **s)
{
	size_t	i;
	char	*word;
	t_env	*home;

	i = 0;
	while ((*s)[i])
	{
		pass_through_quotes(*s, &i, NULL);
		if ((i == 0 && (*s)[i] == '~') ||
			(i > 0 && ft_strchr(" =", (*s)[i - 1]) && (*s)[i] == '~'))
		{
			if ((*s)[i + 1] == '/' || (*s)[i + 1] == '\0' || (*s)[i + 1] == ':')
			{
				home = get_env_var(&data, "HOME");
				word = ft_strsubstitute(*s, "~", home->value, i);
				if (!word)
					return ;
				free(*s);
				*s = word;
				i = i + ft_strlen(home->value) - 1;
			}
		}
		i++;
	}
}

char	*replace_expansion(int exp_len, int replace_len, char ***s, char *replace)
{
	char	*aux;
	size_t	len;
	char	*copy;
	char	*ret;

	copy = ft_strdup((*(*s)));
	len = ft_strlen(copy);
	aux = ft_calloc(sizeof(char), (len - exp_len + replace_len + 1));
	ret = ft_strjoin(replace, &copy[exp_len]);
	free(aux);
	free(copy);
	free((*(*s)));
	return (ret);
}

void	get_exit_status(t_data data, char ***s, char *word)
{
	char	*exit_code;
	int		len_exitcode;

	exit_code = ft_itoa(data.exit_code);
	len_exitcode = ft_strlen(exit_code);
	(*(*s)) = replace_expansion(ft_strlen(word), len_exitcode, s, exit_code);
	free(exit_code);
}

void	env_var_substitution(t_data data, char ***s, size_t *i)
{
	char	*word;
	char	*s_new;
	t_env	*env_var;

	word = ft_strcpy_until((*(*s)) + (*i), " /:");
	ft_printf("\n%s\n", word);
	if (!word)
		return ;
	if (word[1] == '?')
	{
		get_exit_status(data, &s[*i], word);
		return (free(word));
	}
	if (word[1])
	{
		env_var = get_env_var(&data, word + 1);
		if (!env_var)
			s_new = ft_calloc(sizeof(char), 1);
		else
		{
			s_new = ft_strsubstitute((*(*s)), word, env_var->value, *i);
			*i = *i + ft_strlen(env_var->value) - 1;
		}
		free((*(*s)));
		(*(*s)) = s_new;
		if (!s_new)
			return (free(word));
	}
	free(word);
}

void	env_var_expansion(t_data data, char **s)
{
	size_t	i;

	i = 0;
	while ((*s)[0] && (*s)[i])
	{
		pass_through_quotes(*s, &i, NULL);
		if ((*s)[i] == '$')
			env_var_substitution(data, &s, &i);
		i++;
	}
}
