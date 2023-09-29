/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:17:57 by snocita           #+#    #+#             */
/*   Updated: 2023/09/29 15:36:15 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_get_env(t_env *env, char *value_to_fetch)
{
	while (env->value && env->next != NULL)
	{
		if (is_exact_match(env->key, value_to_fetch) == 1)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

//checks that separators are succeded by not separators
// if they do, error is thrown
int	check_line(t_gen *gen, t_token *token)
{
	while (token)
	{
		if (is_types(token, "TAIH")
			&& (!token->next || is_types(token->next, "TAIPEH")))
		{
			unexpected_token_message(token, gen, 1);
			return (0);
		}
		if (is_types(token, "PEH")
			&& (!token->prev || !token->next
				|| is_types(token->prev, "TAIPEH")))
		{
			printf("HEllo1111!");
			unexpected_token_message(token, gen, 0);
			return (0);
		}
		token = token->next;
	}
	return (1);
}

int	is_arg_absent(t_gen	*gen, t_env	*envp, int check)
{
	if ((gen->start->next == NULL) && envp && (check == UNSET))
		return (1);
	if ((gen->start->next == NULL) && envp && (check == EXPORT))
	{
		ft_env(envp);
		return (1);
	}
	if (check == EXPORT && ft_strchr(gen->start->next->str, '=') == NULL)
		return (1);
	if (check == UNSET && ft_strchr(gen->start->next->str, '=') == NULL)
		return (0);
	return (0);
}

size_t	size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

void	get_home_path(char **envp, t_env	*new)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "HOME", 4) != 0)
		i++;
	new->value = ft_strdup(envp[i] + 5);
	return ;
}
