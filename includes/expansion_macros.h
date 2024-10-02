/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_macros.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmeubrin <lmeubrin@student.42berlin.       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:40:11 by lmeubrin          #+#    #+#             */
/*   Updated: 2024/10/02 16:57:06 by lmeubrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_MACROS_H
# define EXPANSION_MACROS_H

enum {
	DOLLAR = 1,
	DQUOTE = 2,
	SQUOTE = 3,
	TILDE = 4,
	SPACE = -1
};

#endif // EXPANSION_MACROS_H
