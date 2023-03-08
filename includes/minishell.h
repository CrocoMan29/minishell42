/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:03:54 by yismaail          #+#    #+#             */
/*   Updated: 2023/03/08 02:28:29 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

typedef struct s_token
{
	int	type;
	char	*value;
}		t_token;

enum {
	TOKEN_WORD,
	TOKEN_CMD,
	TOKEN_INFILE,
	TOKEN_OUTFILE,
	TOKEN_REDIR,
};

#endif