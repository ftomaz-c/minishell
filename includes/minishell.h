#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 199309L

# include "../libft/includes/libft.h"
# include "structs.h"
# include "lexer.h"
# include "parser.h"
# include "builtins.h"
# include "executor.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <dirent.h>

// extern int	global_status;
extern int	g_status;

void minishell(t_tools *tools, char *line);

/*src/utils/signal.c*/
void	handle_sigaction();
void	sig_handler(int	sig);

/*src/utils/tools.c*/
int		config_tools(t_tools *tools, char **envp);
void	update_env(t_tools *tools);

/*tools_utils.c*/
int		compare_var_to_env(char *env, char *var);
void	free_tools(t_tools *tools);
char	**get_env(char **envp);
char	**get_path(char **env);
char	*get_var_from_env(char **env, char *var);

/*src/utils/error.c*/
void	error_check(int argc, char **argv);

/*src/utils/prompt.c*/
char	**handle_home_abreviation(t_tools *tools, char **str);
char	**generate_prompt(t_tools *tools);
char	*prompt_line(t_tools *tools);

/*src/utils/history.c*/
void	write_in_history_file(char **line, int fd, char *file_path);
void	add_history_file(char *line, char *file_name);
void	append_to_history(char *line);
void	update_history(char *file_name);

/*src/utils/history_utils_1.c*/
int		check_empty_line(char *line);
size_t	ft_strlen_nl(const char *s);
int		count_lines_in_file(const char *filename);
int		history_section(char *line);
char	*get_file_path_from_home(char *file_name);

/*src/utils/history_utils_2.c*/
int		count_chr(char *line, char c);
void	treat_line(char ***line_array, char *line);
void	add_line(char *line, char ***line_array, int fd, char *file_path);
int		check_line_count(int line_count, int fd);

/*src/utils/print.c*/
void	print_lexer(t_tools *tools);
void	print_parser(t_tools *tools);

#endif
