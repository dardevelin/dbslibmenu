/*
 * main.c
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


#include "libmenu_menu_interface.h"

int global=0;

void inc(void)
{
    global++;
    printf("global is now %d", global);
    getchar();
}

void dec(void)
{
    global--;
    printf("global is now %d", global);
    getchar();
}

void dys(void)
{
    printf("global is now %d", global);
    getchar();
}

int main(int argc, char **argv)
{
    libmenu_menu_t menu, sub, sub2;
    
    libmenu_init_menu(&menu, "Main Menu");
    libmenu_init_menu(&sub, "Sub Menu");
    libmenu_init_menu(&sub2, "sub sub menu");
    
    menu.add_entry(&menu, "Option One", NULL);
    menu.add_entry(&menu, "show global", dys);
    menu.add_entry(&menu, "increment global", inc);
    menu.add_entry(&menu, "decrement global", dec);
    menu.add_entry(&menu, "Option for next menu", NULL);
    
    sub.add_entry(&sub, "ana option", NULL);
    sub.add_entry(&sub, "phone option", NULL);
    sub.add_entry(&sub, "just another option", NULL);
    
    sub2.add_entry(&sub2, "sub sub opt", NULL);
    sub2.add_entry(&sub2, "sub sub opt2", NULL);
    sub2.add_entry(&sub2, "sub sub opt3", NULL);
    
    sub.add_submenu(&sub, &sub2);
    menu.add_submenu(&menu, &sub);
    
    menu.loop(&menu);

    menu.self_destruct(&menu);
    sub.self_destruct(&sub);  
    sub2.self_destruct(&sub2);


    return 0;
}


