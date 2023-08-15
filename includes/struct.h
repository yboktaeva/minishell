/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuboktae <yuboktae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:09:44 by yuboktae          #+#    #+#             */
/*   Updated: 2023/08/15 18:09:25 by yuboktae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum s_type
{
	WORD,
	DELIMETER,
	FIELD,
	EXP_FIELD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
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
	t_token			*tok;
	t_node			*cmd_node;
	int				count;
	// int				*builtin_ptr[7];
	// char			*reserved_names[7];
}					t_table;

#endif