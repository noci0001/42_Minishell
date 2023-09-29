/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_program_functions2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 15:44:33 by snocita           #+#    #+#             */
/*   Updated: 2023/08/02 17:05:44 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_sig	g_sig;

char	*get_value_from_before_equal(char	*str, int index)
{
	char	*value;

	value = malloc(sizeof(char) * (index + 1));
	if (!value)
	{
		free(str);
		return (NULL);
	}
	index = 0;
	while (str[index] && str[index] != '=')
	{
		value[index] = str[index];
		index++;
	}
	free(str);
	value[index] = '\0';
	return (value);
}

char	*get_value_before_equal(char *str)
{
	size_t	i;

	i = 0;
	if (ft_strchr(str, '=') == NULL)
	{
		free(str);
		return (NULL);
	}
	while (str[i] && str[i] != '=')
		i++;
	return (get_value_from_before_equal(str, i));
}

t_env	*is_inside_envp(t_env *envp, t_gen *gen, int check, char	*str)
{
	char	*to_export;

	if (str != NULL)
		to_export = ft_strdup(str);
	else
		to_export = ft_strdup(gen->start->next->str);
	if (check == EXPORT)
	{
		to_export = ft_strdup_for_envp(gen->start->next->str, 1);
		if (to_export == NULL)
			return (NULL);
	}
	while (envp != NULL)
	{
		if (is_exact_match(envp->key, to_export) == 1)
		{
			free(to_export);
			return (envp);
		}
		envp = envp->next;
	}
	free(to_export);
	return (NULL);
}

void	increase_shlvl(t_env	*env)
{
	int		level_number;
	char	*itoa_string;

	while (env && (ft_strncmp("SHLVL", env->key, 5) != 0))
		env = env->next;
	level_number = ft_atoi(env->value);
	level_number++;
	itoa_string = ft_itoa(level_number);
	free(env->value);
	env->value = ft_strdup(itoa_string);
	free(itoa_string);
	return ;
}

void	sig_init(void)
{
	turn_off_echo();
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}
