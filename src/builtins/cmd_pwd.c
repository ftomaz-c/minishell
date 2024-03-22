#include "../../includes/builtins.h"
/**
 * @brief Prints the current working directory.
 * 
 * This function prints the current working directory to the standard output.
 * 
 * @param tools   Pointer to the tools struct containing necessary information.
 * @param command Pointer to the parser struct containing command information.
 * 
 * @return The global status after executing the pwd command.
 * 
 * @note This function assumes the validity of the tools and command structs.
 * 
 * @warning Behavior is undefined if tools or command is NULL.
 * 
 * @see printf, getcwd, global_status
 * 
 * @example
 * ```
 * // Example usage of pwd function
 * t_tools *tools = initialize_tools(); // Initialize tools struct
 * t_parser *command = initialize_parser(); // Initialize parser struct
 * int status = pwd(tools, command); // Execute the pwd command
 * // status will be the global status after executing the pwd command.
 * ```
 */

int	cmd_pwd(t_tools *tools, t_parser *command)
{
	char	buf[1024];

	(void)tools;
	(void)command;
	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		free(tools->pwd);
		free(tools->oldpwd);
		tools->pwd = get_var_from_env(tools->env, "PWD");
		tools->oldpwd = get_var_from_env(tools->env, "OLDPWD");
		ft_strcpy(buf, tools->pwd);
	}
	printf("%s\n", buf);
	g_status = EXIT_SUCCESS;
	return (g_status);
}