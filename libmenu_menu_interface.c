/*
 * libmenu_menu_interface.c
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

#ifdef LIBMENU_CUSTOM_CONFIG
    #include "libmenu_config.h"
#else
    #define LIBMENU_DEFAULT_CONFIG
    
    #define LIBMENU_BUFF_SIZE   256
    #define LIBMENU_SYS_CLEAR_OP    "clear"
    #define LIBMENU_RETURN_MSG "return"
    #define LIBMENU_SELECT_ERR_MSG "invalid! "
    #define LIBMENU_DECIMAL_BASE  10
#endif

//helper function strdup
char *_newstr(const char *str)
{
    char *ret;
    size_t slen = strlen(str);
    
    if(slen == 0)
        return NULL;
        
    if( (ret = malloc(slen+1))==NULL)
        return NULL;
    
    memcpy(ret,str,slen);
    ret[slen]='\0';
    return ret;
}
void libmenu_self_destruct(libmenu_menu_t *main)
{
    if(main->menu != NULL)
        libmenu_delete_list(&main->menu);
    
    if(main->title != NULL)
        free(main->title);
}

void libmenu_init_menu(libmenu_menu_t *main,
    char *title)
{
    libmenu_init_list(&main->menu);

    main->title = _newstr(title);
    main->lastappend = NULL;
    main->add_entry = libmenu_add_entry;
    main->add_submenu = libmenu_add_submenu;
    main->self_destruct = libmenu_self_destruct;
    main->loop = libmenu_main_loop;

}

void libmenu_add_entry(libmenu_menu_t *main,
    char *label, void(*f)(void))
{
    libmenu_node_t *ptrnode;
    
    ptrnode = libmenu_create_node(label);
    if(ptrnode == NULL )
    {
        fprintf(stderr,
            "libmenu_internal error, could not create entry");
    }
    
    libmenu_set_trigger(ptrnode,f);
    
    ptrnode->submenu = NULL;
    
    main->lastappend = ptrnode;
    libmenu_push_node(&main->menu, ptrnode);
    
    return;
}

void libmenu_add_submenu(libmenu_menu_t *main, libmenu_menu_t *sub)
{
    if( main->lastappend == NULL)
    {
        fprintf(stderr,
            "libmenu: add_submenu error, requires top level option");
        return;
    }
    
    libmenu_set_submenu(&main->lastappend, &sub->menu);

    return;
}

long int libmenu_main_loop_getopt()
{
    char buff[LIBMENU_BUFF_SIZE];
    printf(">>");
    fgets(buff,LIBMENU_BUFF_SIZE, stdin);
    
    return strtol(buff, NULL, LIBMENU_DECIMAL_BASE);
}

bool libmenu_opt_validator(long int *op, long int *nopt)
{
    //valid = false - invalid = true
    if(*op > *nopt)
        return true;
    
    if(*op < 0)
        return true;
    
        
    return false;
}

void libmenu_init_menu_internal(libmenu_menu_t *main,
    libmenu_list_t *sub)
{
    main->menu  = *sub;
    main->title = (*sub)->label;
    main->lastappend = NULL;
    main->add_entry = NULL;
    main->add_submenu = NULL;
    main->self_destruct = NULL;
    main->loop = libmenu_main_loop;
}

void libmenu_main_loop(libmenu_menu_t *main)
{
    libmenu_node_t *ptr = main->menu;
    size_t i, t; //generic iterators
    long int op=-2; //to start with a non option
    long int nopt=0;
    bool was_invalid = false;
    
    //count how many options exist
    for(nopt=0; ptr != NULL; nopt++)
        ptr = ptr->next;
    
    //start menu cycle
    do
    {
        //need to create macro configuration
        system(LIBMENU_SYS_CLEAR_OP);
        
        //show menu title
        if(main->title != NULL)
            printf("%s:\n\n", main->title);
        
        //show options
        for(i=0, ptr = main->menu; ptr != NULL; ptr = ptr->next, i++)
        {
            printf("[%zu]\t", i);
            libmenu_show_node(ptr);
            putchar('\n');
        }
        
        //show return option
        printf("[%zu]\t", nopt);
        printf("%s\n", LIBMENU_RETURN_MSG);
        
        //the selected option was invalid
        if( was_invalid == true )
        {
            was_invalid = false;
            printf(LIBMENU_SELECT_ERR_MSG);
        }
        
        op = libmenu_main_loop_getopt();
        if((was_invalid = libmenu_opt_validator(&op, &nopt))== true)
            continue;
        
        if(op==nopt)
            break;
        
        //find option
        ptr = main->menu;    
        for(t=0; t<op; t++)
        {
            if(ptr->next != NULL )
                ptr = ptr->next;
        }
        
        if(ptr->submenu != NULL )
        {
            libmenu_menu_t tmp;
            libmenu_init_menu_internal(&tmp, ptr->submenu);
            tmp.loop(&tmp);
        }
        
        if(ptr->trigger != NULL )
            ptr->trigger();
    }
    while(1);
    
    return;
}


