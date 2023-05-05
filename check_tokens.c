#include "includes/minishell.h"

void    check_tokens(t_token *token)
{
    t_token	*tmp;

    tmp = token;
    printf("--------CHECK_TOKENS-----------\n");
    while (tmp)
    {
		printf("content = %s\n", tmp->content);
        printf("type    = %d\n", tmp->type);
		tmp = tmp->next;
	}
}

void    get_input(t_cmd *command)
{
    t_cmd *cmd;
    int     i;
    int     x;

    cmd = command;
	printf("-------TABLE-----------\n");
	i = 0;
	while (cmd)
    {
        x = 0;
        while (cmd->cmd[x])
        {
            printf("[node:%d] cmd[%d] = %s\n", i, x, cmd->cmd[x]);
            x++;
        }
		printf("[node:%d] pipe   = %d\n", i,cmd->pipe);
		printf("[node:%d] er     = %d\n", i,cmd->err);
        printf("----------------------------\n");
		i++;
		cmd = cmd->next;
	}    
}
