/*
 * libmenu_linked_list.h
 * This file is part of dbslibmenu
 *
 * Copyright (C) 2012 - Darcy Brás da Silva
 *
 * dbslibmenu is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * dbslibmenu is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dbslibmenu. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef LIBMENU_LINKED_LIST_H
#define LIBMENU_LINKED_LIST_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct sLibMenuNode  libmenu_node_t;
typedef struct sLibMenuNode* libmenu_list_t;
struct sLibMenuNode {
	char *label;
    void (*trigger)(void);
    libmenu_list_t *submenu;
    libmenu_node_t *next;
};

/* the functions suffixed with _s don't copy the
	labels, they just point to the string literals
*/


void libmenu_init_list(libmenu_list_t*);
libmenu_node_t *libmenu_create_node(char *);

libmenu_node_t *libmenu_create_node_s(char*);

libmenu_node_t *libmenu_push_node(libmenu_list_t*, libmenu_node_t*);

libmenu_node_t *libmenu_pop_node(libmenu_list_t*);

void libmenu_delete_node(libmenu_node_t*);

void libmenu_delete_node_s(libmenu_node_t*);

void libmenu_delete_list(libmenu_list_t*);

void libmenu_delete_list_s(libmenu_list_t*);

void libmenu_set_trigger(libmenu_node_t*, 
	void(*f)(void));

void libmenu_set_submenu(libmenu_list_t *,libmenu_list_t *);

void libmenu_show_node(libmenu_node_t *);

void libmenu_show_list(libmenu_list_t *);


#endif
