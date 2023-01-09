/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoler <asoler@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:08:18 by vfranco-          #+#    #+#             */
/*   Updated: 2023/01/01 23:02:31 by asoler           ###   ########.fr       */
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

char	*get_value(t_data data, char *word)
{
	char	*value;
	t_env	*aux;

	if (word[1] == '?')
		value = ft_itoa(data.exit_code);
	else
	{
		aux = get_env_var(&data, word + 1);
		if (!aux)
			value = NULL;
		else
			value = ft_strdup(aux->value);
	}
	return (value);
}

void	env_var_substitution(t_data data, char ***s, size_t *i)
{
	char	*word;
	char	*s_new;
	char	*value;

	word = ft_strcpy_until((*(*s)) + (*i), " /:");
	if (!word)
		return ;
	if (word[1])
	{
		value = get_value(data, word);
		if (!value)
			s_new = ft_calloc(sizeof(char), 1);
		else
		{
			s_new = ft_strsubstitute((*(*s)), word, value, *i);
			*i = *i + ft_strlen(value) - 1;
		}
		free((*(*s)));
		(*(*s)) = s_new;
	}
	free(value);
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
