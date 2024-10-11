/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:26:45 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/11 13:21:40 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

/* Instructions describing what kind of thing to do for a redirection. */
enum	e_red_instruction {
	r_output_direction,	r_input_direction, r_inputa_direction,
	r_appending_to,	r_reading_until, r_reading_string,
	r_duplicating_input,	r_duplicating_output, r_deblank_reading_until,
	r_close_this,	r_err_and_out, r_input_output, r_output_force,
	r_duplicating_input_word,	r_duplicating_output_word,
	r_move_input,	r_move_output, r_move_input_word, r_move_output_word,
	r_append_err_and_out
};

/* A structure which represents a word. */
typedef struct s_word_desc {
	char	*word;		/* Zero terminated string. */
	int		flags;		/* Flags associated with this word. */
}	t_word_desc;

/*	A linked list of words. */
typedef struct s_word_list {
	struct s_word_list	*next;
	t_word_desc			*word;
}	t_word_list;

//	REDIRECTION

//	contains fd or file to redirect to
typedef union s_redirectee {
	int	dest;			/* Place to redirect REDIRECTOR to, or ... */
	t_word_desc	*filename;		/* filename to redirect to. */
}	t_redirectee;

/*	Structure describing a redirection.	If REDIRECTOR is negative, the parser
		(or translator in redir.c) encountered an out-of-range file descriptor. */
typedef struct s_redirect {
	struct	redirect *next;	/* Next element, or NULL. */
	t_redirectee	redirector;	/* Descriptor or varname to be redirected. */
	int	rflags;			/* Private flags for this redirection */
	int	flags;			/* Flag value for `open'. */
	enum	e_red_instruction  instruction; /* What to do with the information. */
	t_redirectee	redirectee;	/* File descriptor or filename */
	char	*here_doc_eof;		/* The word that appeared in <<foo. */
}	t_redirect;

/*	An element used in parsing.	A single word or a single redirection.
		This is an ephemeral construct. */
typedef struct s_element {
	t_word_desc	*word;
	t_redirect	*redirect;
}	t_element;

#endif // !REDIRECT_H
