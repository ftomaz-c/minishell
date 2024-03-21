#include "../../includes/minishell.h"

int	compare_var_to_env(char *env, char *var)
{
	int	i;

	i = 0;
	while (env[i] != '=' && env[i] && var[i])
	{
		if (env[i] == var[i])
			i++;
		else
			return (0);
	}
	if (var[i] == '\0' && env[i] == '=')
		return (1);
	return (0);
}

/**
 * @brief Frees the memory allocated for the tools structure.
 * 
 * This function frees the memory allocated for the tools
 * structure, including its
 * environment variables, path list, current working directory,
 * and previous working directory.
 * 
 * @param tools A pointer to the tools structure.
 * 
 * @return None.
 * 
 * @note Assumes the tools structure is properly initialized.
 * 
 * @see config_tools
 * 
 * @warning Make sure to call this function to avoid memory leaks
 * after using the tools structure.
 * 
 */

void	free_tools(t_tools *tools)
{
	if (!tools)
		return ;
	if (tools && tools->env)
		free_list(tools->env);
	if (tools && tools->path)
		free_list(tools->path);
	if (tools && tools->pwd)
		free(tools->pwd);
	if (tools && tools->oldpwd)
		free(tools->oldpwd);
	if (tools && tools->home)
		free(tools->home);
	if (tools && tools->user)
		free(tools->user);
	if (tools && tools->name)
		free(tools->name);
}

/**
 * @brief Retrieves the value of a variable from the environment.
 * 
 * This function searches the environment variables
 * for a specific variable
 * and returns its value.
 * 
 * @param envp The array of environment variables.
 * @param var The name of the variable to retrieve.
 * 
 * @return A pointer to the value of the variable if found,
 * or NULL if not found or on error.
 * 
 * @note Assumes envp is a valid array of environment variables.
 * 
 * @see get_env
 * 
 * @warning Make sure to free the memory allocated for the returned string.
 * 
 * @example
 * 
 * ```
 * char *value = get_var_from_env(envp, "PATH=");
 * if (value != NULL) {
 *     printf("PATH: %s\n", value);
 *     free(value);
 * }
 * ```
 */

char	*get_var_from_env(char **env, char *var)
{
	int		index;
	char	*value;

	index = 0;
	if (!env || !var)
		return (NULL);
	while (env[index])
	{
		if (compare_var_to_env(env[index], var))
			break ;
		index++;
	}
	if (env[index])
		value = ft_substr(env[index], ft_strlen(var) + 1,
				ft_strlen(env[index]));
	else
		value = NULL;
	return (value);
}

/**
 * @brief Copies the environment variables into a new array.
 * 
 * This function creates a copy of the environment variables
 * and stores them
 * in a new dynamically allocated array.
 * 
 * @param envp The array of environment variables.
 * 
 * @return A pointer to the new array of environment variables,
 * or NULL on error.
 * 
 * @note Memory allocated for the returned array and its elements
 * must be freed by the caller.
 * 
 * @see config_tools
 * 
 * @warning The caller is responsible for freeing the memory allocated
 * for the returned array and its elements.
 * 
 * @example
 * 
 * ```
 * char **env = get_env(envp);
 * if (env != NULL) {
 *     // Use env...
 *     free_env(env);
 * }
 * ```
 */

char	**get_env(char **envp)
{
	char	**env;
	int		count;
	int		index;

	count = 0;
	if (!envp)
		return(NULL);
	while (envp[count])
		count++;
	env = ft_calloc(sizeof(char *), count + 1);
	if (env == NULL)
		return (NULL);
	index = 0;
	while (envp[index])
	{
		env[index] = ft_strdup(envp[index]);
		if (env[index] == NULL)
			return (NULL);
		index++;
	}
	return (env);
}

/**
 * @brief Retrieves the value of the PATH variable from the
 * environment and splits it into individual paths.
 * 
 * This function retrieves the value of the PATH variable from the environment,
 * splits it into individual paths separated by colons, and
 * stores them in an array.
 * 
 * @param env The array of environment variables.
 * 
 * @return A pointer to the array of path strings, or NULL on error.
 * 
 * @note Memory allocated for the returned array and its elements
 * must be freed by the caller.
 * 
 * @see config_tools
 * 
 * @warning The caller is responsible for freeing the memory allocated
 * for the returned array and its elements.
 * 
 * @example
 * 
 * ```
 * char **path_list = get_path(env);
 * if (path_list != NULL) {
 *     // Use path_list...
 *     free_path_list(path_list);
 * }
 * ```
 */

char	**get_path(char **env)
{
	char	*path_from_envp;
	char	**path_list;

	path_from_envp = get_var_from_env(env, "PATH");
	if (!path_from_envp)
	{
		ft_putstr_fd("minishell: No such file or directory\n", STDERR_FILENO);
		g_status = 127;
		exit (g_status);
	}
	path_list = ft_split(path_from_envp, ":");
	free(path_from_envp);
	if (!path_list)
		return (NULL);
	return (path_list);
}