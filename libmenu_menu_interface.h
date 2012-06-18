/*
 * libmenu_menu_interface.h
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


#ifndef LIBMENU_MENU_INTERFACE_H
#define LIBMENU_MENU_INTERFACE_H

#include <stdbool.h>
#include "libmenu_linked_list.h"

//menu interface datatypes
typedef struct sLibMenuInterface  libmenu_menu_t;
struct sLibMenuInterface {
    libmenu_list_t menu;
    libmenu_node_t *lastappend;
    char *title;
    void (*add_entry)(libmenu_menu_t*,char*,void(*f)(void));
    void (*add_submenu)(libmenu_menu_t*,
        libmenu_menu_t*);
    
    void (*loop)(libmenu_menu_t*);
    
    void (*self_destruct)(libmenu_menu_t*);

};

void libmenu_init_menu(libmenu_menu_t*,char*);

void libmenu_add_entry(libmenu_menu_t *,char*,
    void(*f)(void));

void libmenu_add_entry_s(libmenu_menu_t *,char*,
    void(*f)(void));

void libmenu_add_submenu(libmenu_menu_t*,
    libmenu_menu_t*);

void libmenu_self_destruct(libmenu_menu_t*);

void libmenu_main_loop(libmenu_menu_t*);


#endif
