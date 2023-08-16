/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:09:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/16 17:54:56 by yuboktae         ###   ########.fr       */
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

// typedef struct	s_list /*important for ENVP*/
// {
// 	void	*key;
// 	void	*value;
// }				t_list;

typedef struct s_node
{
	char			**cmd_args;
	void	*redirect_in_node;
	void	*redirect_out_node;
	void	*heredoc_node;
	void	*pipe_node;
}					t_node;

typedef struct s_table
{
	char			**cmds;
	char			*cmd_path;
	char			**envp;
	t_token			*tok;
	t_node			*cmd_node;
	int				count;
	// int				*builtin_ptr[7];
	// char			*reserved_names[7];
}					t_table;

#endif