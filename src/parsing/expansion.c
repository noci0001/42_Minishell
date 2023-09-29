/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:06:11 by snocita           #+#    #+#             */
/*   Updated: 2023/08/06 16:20:27 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	expansion_function(t_gen	*gen, t_token	*token)
{
	char	*ret;
	int		pid;

	if (token->str[1] == '$')
	{
		pid = getpid();
		ret = ft_itoa(pid);
		free(token->str);
		token->str = NULL;
		if (ret != NULL)
			token->str = ft_strdup(ret);
		free(ret);
	}
	else
	{
		ret = expansion_string(gen, token->str, 0);
		free(token->str);
		token->str = NULL;
		if (ret != NULL)
			token->str = ft_strdup(ret);
		free(ret);
	}
	return ;
}

void	check_expansion(t_gen *gen, t_token *token)
{
	int		i;
	char	*ret;
	char	*new_value;

	ret = NULL;
	new_value = NULL;
	i = 0;
	if (token->str[0] == '$' && token->exp_disabled != 1)
		expansion_function(gen, token);
	while (token->str && token->str[i])
	{
		if (token->str[i] == '$' && token->exp_disabled != 1)
		{
			ret = expansion_string(gen, token->str, i);
			new_value = ft_substr(token->str, 0, i);
			free(token->str);
			token->str = ft_strjoin(new_value, ret);
			if (ret != NULL)
				free(ret);
			free(new_value);
			break ;
		}
		i++;
	}
}

char	*expansion_string(t_gen *gen, char *str, int index)
{
	char	*string;
	t_env	*node;

	if (str[0] == '$' && str[1] == '?')
		return (ft_itoa(gen->ret));
	string = ft_substr(str, ++index, ft_strlen(str));
	node = is_inside_envp(gen->env, gen, 0, string);
	if (node != NULL)
	{
		free(string);
		return (node->value);
	}
	free(string);
	return (NULL);
}
