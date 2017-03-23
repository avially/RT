/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keywords.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avially <avially@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 00:14:55 by alelievr          #+#    #+#             */
/*   Updated: 2017/03/23 01:46:07 by avially          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYWORDS_H
# define KEYWORDS_H

const char * g_restricted_keywords[] = {
	"type:", "pos:", "rot:", "color:", "csg:", "radius:", "scale:", "slice:",
	"mtl:", "mesh:", "filter:", "texture:", "emission color:",
	"highlight color:", "transparency:", "reflection:", "refraction:",
	"bumpmap:", "illum:", "emission color map", "highlight color map",
	"refraction map", "reflection map", "ambiant color", NULL
};

#endif
