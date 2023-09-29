/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amurawsk <amurawsk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:02:33 by snocita           #+#    #+#             */
/*   Updated: 2023/08/03 15:02:16 by amurawsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_token	*loop_through_line(char *line, int index)
{
	t_token	*prev;
	t_token	*next;
	int		sep;

	prev = NULL;
	next = NULL;
	while (line[index])
	{
		sep = ignore_sep(line, index);
		next = next_token(line, &index);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next, sep);
		ft_skip_space(line, &index);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

void	squish_args2(t_gen *gen, t_token *token, t_token	*prev)
{
	while (is_last_valid_arg(prev) == 0)
		prev = prev->prev;
	token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	token->prev = prev;
	if (prev != NULL)
		token->next = prev->next;
	else
		token->next = gen->start;
	if (prev == NULL)
		prev = token;
	prev->next->prev = token;
	if (gen->start->prev != NULL)
		prev->next = prev->next;
	else
		prev->next = token;
	if (gen->start->prev != NULL)
		gen->start = gen->start->prev;
	else
		gen->start = gen->start;
}

// token->next = (prev) ? prev->next : gen->start;
// prev = (prev) ? prev : token;
// prev->next->prev = token;
// prev->next = (gen->start->prev) ? prev->next : token;
// gen->start = (gen->start->prev) ? gen->start->prev : gen->start;
void	squish_args(t_gen *gen)
{
	t_token	*token;
	t_token	*prev;

	token = gen->start;
	while (token)
	{
		prev = prev_sep(token, NOSKIP);
		if (is_type(token, ARG) && is_types(prev, "TAI"))
		{
			while (is_last_valid_arg(prev) == 0)
				prev = prev->prev;
			squish_args2(gen, token, prev);
		}
		token = token->next;
	}
}

//through strcmp this function determines
// which type of arg it is
//possibilities are: "> >> < | ;"
void	type_arg(t_token *token, int separator)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0 && separator == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0 && separator == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<<") == 0 && separator == 0)
		token->type = HEREDOC;
	else if (ft_strcmp(token->str, "<") == 0 && separator == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0 && separator == 0)
		token->type = PIPE;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

//allocate space for the interception of
// the next token
int	next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count--;
	}
	return (j - count + 1);
}
