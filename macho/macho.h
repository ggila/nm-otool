/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/13 16:24:15 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/13 17:28:41 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACHO_H
# define MACHO_H

# include "ft_printf.h"



/*
** from /usr/include/mach-o/loader.h
**     struct mach_header {
**     	uint32_t	magic;		// mach magic number identifier 
**     	cpu_type_t	cputype;	// cpu specifier 
**     	cpu_subtype_t	cpusubtype;	// machine specifier 
**     	uint32_t	filetype;	// type of file 
**     	uint32_t	ncmds;		// number of load commands 
**     	uint32_t	sizeofcmds;	// the size of all the load commands 
**     	uint32_t	flags;		// flags 
**     };
*/

/*
** from machine.h
**    typedef integer_t	cpu_type_t;
**    typedef integer_t	cpu_subtype_t;
*/


void	*map_file(char *file);

#endif
