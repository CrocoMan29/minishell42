/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:32:33 by meharit           #+#    #+#             */
/*   Updated: 2023/06/09 20:40:57 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    dup_it(int phase, int i)
{
    if (phase == 0)  //first cmd
        dup2(exec.pipes[0][1], 1);

    if (i % 2 == 0)
    {
        if (phase == 1) // middle cmd
        {
            dup2(exec.pipes[0][1], 1);
            dup2(exec.pipes[1][0], 0);
        }
        if (phase == 2) //last cmd
            dup2(exec.pipes[1][0], 0);
    }

    else
    {
        if (phase == 1) //middle cmd
        {
            dup2(exec.pipes[1][1], 1); // i % 2 != 0
            dup2(exec.pipes[0][0], 0);
        }
        
        if (phase == 2) //last cmd
            dup2(exec.pipes[0][0], 0);
    }
    close(exec.pipes[1][1]);
    close(exec.pipes[0][0]);
    close(exec.pipes[0][1]);
    close(exec.pipes[1][0]);
}

void    execute_cmds(t_cmd *table, t_env *env, int phase, int i)
{
    char    *cmd_path;
    char    *cmd;
    
    (void)phase;
    
    cmd_path = cmd_exist(table, env);
    dup_it(phase, i);
    redir_in(table, i);
    redir_out(table);
    if (table->cmd) // there is a commad
    {
        cmd = table->cmd[0];
        if (is_builtin(cmd))
            which_builtin(cmd, table, &env, TRUE);
        if (!cmd_path)
        {
            ft_putstr_fd("minishell: ", 2);
            ft_putstr_fd(cmd, 2);
            ft_putstr_fd(": command not found\n", 2);
            exec.g_exit_status = 127;
            exit (exec.g_exit_status);
        }
        if (execve(cmd_path, table->cmd, exec.env) == -1)
        {
            perror("");
            exec.g_exit_status = 126;
        }
    }
    exit (exec.g_exit_status);
}
