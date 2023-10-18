/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:34:58 by snocita           #+#    #+#             */
/*   Updated: 2023/08/01 17:35:34 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_match(t_env	*env)
{
	if (ft_strncmp(env->key, "PATH", 4) == 0)
		return (SUCCESS);
	else
		return (GENERALERROR);
}

int	continue_execution(t_env *env, char **args, t_gen *gen)
{
	int		i;
	int		ret;
	char	**bin;
	char	*path;

	i = 1;
	ret = GENERALERROR;
	if (env == NULL || env->next == NULL)
	{
		ret = magic_box(args[0], args, env, gen);
		return (ret);
	}
	bin = ft_split(env->value, ':');
	if (allocate_bin(bin, env, args) == GENERALERROR)
		return (ret);
	path = check_dir(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);
	ret = execute_depending_on_path(path, args, env, gen);
	return (free_tab(bin), free(path), ret);
}
