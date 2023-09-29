/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 17:58:03 by snocita           #+#    #+#             */
/*   Updated: 2023/08/03 16:54:16 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	here_doc(t_gen	*gen, t_token *token)
{
	gen->fdin = open(".secretfile", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (gen->fdin == -1)
	{
		gen->ret = GENERALERROR;
		gen->no_exec = 1;
		return (ft_putstr_fd("Handling here_doc failed\n", 2));
	}
	return (here_doc2(gen, token));
}

void	here_doc2(t_gen	*gen, t_token *token)
{
	char	*line;

	while (1)
	{
		line = readline("<< ");
		if (is_exact_match(line, token->str))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, gen->fdin);
		ft_putstr_fd("\n", gen->fdin);
		free(line);
	}
	close(gen->fdin);
	gen->fdin = open(".secretfile", O_RDONLY, 0777);
	dup2(gen->fdin, STDIN_FILENO);
	close(gen->fdin);
	unlink(".secretfile");
}
