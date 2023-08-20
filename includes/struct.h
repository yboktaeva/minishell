/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuliaboktaeva <yuliaboktaeva@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:09:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/20 22:24:17 by yuliaboktae      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	FIELD,
	EXP_FIELD
}			t_type;

typedef struct s_token
{
	t_type	type;
	char	*value;
	int		len;
}				t_token;

typedef struct s_redir /*structure for redirections IN, OUT, HEREDOC, APPEND*/
{
	t_type	type;
	char	*file_name;
}				t_redir;

typedef struct s_node
{
	char	**cmd_args;
	void	*pipe_node;
	t_redir	*input;
	t_redir	*output;
}				t_node;

typedef struct s_table
{
	char			**cmds;
	char			*cmd_path;
	char			**envp;
	t_token			*tokens;
	t_node			*cmd_node;
	int				count;
	int				n_tokens;
	// int				*builtin_ptr[7];
	// char			*reserved_names[7];
}				t_table;

// typedef struct	s_env /*important for ENVP*/
// {
//		char	*str;
// 		void	*key;
// 		void	*value;
//		struct s_env	*next;
// }				t_env;

#endif