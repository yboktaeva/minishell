/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:09:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/23 17:02:03 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_type
{
	WORD,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	PIPE
}			t_type;

typedef struct s_token
{
	t_type	type;
	char	*value;
}			t_token;

typedef struct s_redir /*structure for redirections IN, OUT, HEREDOC, APPEND*/
{
	t_type	type;
	char	*file_name;
}			t_redir;

typedef struct s_node
{
	char	**cmd_args;
	void	*pipe_node;
	t_redir	*input;
	t_redir	*output;
}			t_node;

typedef struct	s_env /*extract ENVP in structure*/
{
	char	*key;
	char	*value;
	struct s_env	*next;
}				t_env;

typedef struct s_table
{
	t_env			*env;
	char			**cmds;
	char			*path;
	t_token			*tokens;
	t_node			*cmd_node;
	int				n_tokens;
	int				cmd_count;
	int				exit_status;
	// int			*builtin_ptr[7];
	// char			*reserved_names[7];
}			t_table;


#endif