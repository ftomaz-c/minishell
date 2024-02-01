
#include "../includes/minishell.h"

int	check_if_token(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&')
		return (1);
	return (0);
}

void	init_lexer(t_lexer *lexer)
{
	lexer->words = NULL;
	lexer->token = NULL;
	lexer->i = 0;
	lexer->next = NULL;
	lexer->pre = NULL;

}

int	check_if_quotes_pair(char *line) // checks if the quotes are paired, based on the first quote type found
{
	int	i;
	int	first;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	first = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (line[i])
	{
		if (line[i] == 34)
		{
			if (single_quotes == 0)
				first = 1;
			double_quotes += 1;
		}
		else if (line[i] == 39)
		{
			if (double_quotes == 0)
				first = 2;
			single_quotes += 1;	
		}
		i++;
	}
	if (first == 1)
	{
		if (double_quotes && double_quotes % 2 != 0)
			return (0);	
	}
	if (first == 2)
	{
		if (single_quotes && single_quotes % 2 != 0)
			return (0);
	}
	return (1);
}

int	exit_simple_error(char *msg)
{
	printf("%s\n", msg);
	return (0);
}
		// newnode = malloc(sizeof(t_lexer));
		// if (!newnode)
		// 	return ;

// void	add_line_lexer_struct(char **line_split, t_lexer *lexer)
// {
// 	int	i;
// 	int	j;
// 	// t_lexer *newnode;

// 	i = 0;
// 	j = 0;
// 	while (line_split[i])
// 	{
// 		while (line_split[i][j])
// 		{

// 		}

// 	}
// }

int	lex_line(char *line, t_lexer *lexer)
{
	char	*line_trimmed;
	char	**line_split_quotes;

	init_lexer(lexer);
	line_trimmed = ft_strtrim(line, " "); //remove initial and final spaces
	// if (line_trimmed && !check_if_quotes_pair(line_trimmed)) // check if quotes are valid (in pairs)
	// {
	// 	free(line_trimmed);
	// 	return (exit_simple_error("error"));	
	// }
	line_split_quotes = ft_split_quotes(line_trimmed, ' '); // splits quotes considering the quotes present
	// line_split_tokens = 
	// add_line_to_lexer_struct(line_split, lexer); // next step -> separate words from the tokens found
	
	// 					Uncomment section bellow to see splitted line
	int	i = 0;
	while (line_split_quotes[i])
	{
		printf("word: %s\n", line_split_quotes[i]);
		free(line_split_quotes[i]);
		i++;
	}
	return (1);
}