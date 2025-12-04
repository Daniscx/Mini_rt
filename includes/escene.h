/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escene.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaestro <dmaestro@student.42madrid.con    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 16:43:48 by dmaestro          #+#    #+#             */
/*   Updated: 2025/12/03 16:55:44 by dmaestro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ESCENE_H
#define ESCENE_H

typedef struct  escene_s    escene_t;

escene_t *escene_constructor(char *file);
void    escene_destructor(escene_t *escene);

#endif