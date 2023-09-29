/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snocita <snocita@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:50:19 by snocita           #+#    #+#             */
/*   Updated: 2023/07/28 17:50:28 by snocita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_str_home_path(char **envp)
{
	int		i;
	char	*temp;

	i = 0;
	while (ft_strncmp(envp[i], "HOME", 4) != 0)
		i++;
	temp = ft_strdup(envp[i] + 5);
	return (temp);
}
