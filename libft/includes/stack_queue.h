/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_queue.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaplyar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 17:18:52 by akaplyar          #+#    #+#             */
/*   Updated: 2017/06/19 17:18:54 by akaplyar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_QUEUE_H
# define STACK_QUEUE_H

# include "libft.h"
# include <stdlib.h>

void		stack_push(void *item, size_t size);
void		*stack_pop();
void		*stack_peek();
void		enqueue(void *item, size_t size);
void		*dequeue();
void		*queue_peek();

#endif
