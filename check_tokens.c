#include "includes/minishell.h"

void	check_tokens(t_token *token)
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
	printf("----------------------------\n");
}

void    get_input(t_cmd *command)
{
	
    t_cmd *cmd;
	t_redi *in;
	t_redi *out;

    int     i;
    int     x;
	
    cmd = command;
	printf("----------TABLE-------------\n");
	i = 0;
	while (cmd)
    {
        x = 0;
        while (cmd->cmd && cmd->cmd[x])
        {
            printf("[node:%d] cmd[%d] = %s\n", i, x, cmd->cmd[x]);
            x++;
        }
		printf("[node:%d] pipe   = %d\n", i,cmd->pipe);
		printf("[node:%d] er     = %d\n", i,cmd->err);
        if (cmd->in)
        {
			in = cmd->in;
			while (in)
			{
				printf("-------------in-------------\n");
				printf("type = %d\n", in->type);
				printf("file = %s\n", in->file);
				printf("m_expd = %d\n", in->must_exp);
				in = in->next;
			}
        }
        if (cmd->out)
        {
			out = cmd->out;
			while (out)
			{
			  printf("-------------out------------\n");
			  printf("type = %d\n", out->type);
			  printf("file = %s\n", out->file);
			  printf("m_expd = %d\n", out->must_exp);
			  out = out->next;
			}
        }
        printf("----------------------------\n");
		i++;
		cmd = cmd->next;
	}
	printf("\n");
}
