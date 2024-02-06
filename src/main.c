#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_lexer	*lexer;
	t_tools	tools;

	(void)argc;
	(void)argv;
	update_history();
	(void)envp;
	error_check(argc, argv);
	while (1)
	{
		if (!config_tools(&tools, envp))
		{
			printf ("Error: Failed to allocate memory for tools\n");
			free_tools(&tools);
			exit (EXIT_FAILURE);
		}
		line = readline("\033[1;32mminishell\033[0m \033[1;34m➜\033[0m  ");
		add_history_file(line);
		if (!lex_line(line, &lexer, tools.env))
		{
			free(line);
			return (1);
		}
		free_tools(&tools);
		free_lexer(&lexer);
		free(line);
	}
	return (0);
}
