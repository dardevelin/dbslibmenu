/*
 * libmenu_linked_list.c
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


#include "libmenu_linked_list.h"
//#include "libmenu_config.h"

void libmenu_init_list(libmenu_list_t *head)
{
    *head = NULL;
    return;
}

libmenu_node_t *libmenu_create_node(char *label)
{
    libmenu_node_t *node;
    size_t llen = strlen(label);
    
    if(llen <= 0)
        return NULL;
    
    if( (node = malloc(sizeof(libmenu_node_t)))==NULL) 
    {
        fprintf(stderr,"libmenu_internal error,malloc failed\n");
        return NULL;
    }
    
    if( (node->label = malloc(llen+1))==NULL) 
    {
        fprintf(stderr,"libmenu_internal error,malloc failed\n");
        free(node);
        return NULL;
    }
    
    memcpy(node->label,label,llen);
    node->label[llen] = '\0'; //make sure it's terminated
    node->trigger = NULL;     //set trigger to NULL for safety
    node->submenu = NULL;   
    node->next = NULL;
    
    return node;   
}//end libmenu_create_node(const char *label);

libmenu_node_t *libmenu_create_node_s(char *label)
{
    libmenu_node_t *node;
    
    if( (node = malloc(sizeof(libmenu_node_t)))==NULL)
    {
        fprintf(stderr,"libmenu_internal error,malloc failed\n");
        return NULL;
    }
    
    node->label = label;
    node->submenu = NULL;
    node->next = NULL;
    
    return node;
}

libmenu_node_t *libmenu_push_node(libmenu_list_t *head, libmenu_node_t *node)
{
	libmenu_node_t *ptrnode = *head;
	
	if(node == NULL)
		return node;
	
	if( *head == NULL )
	{
		*head = node;
		return node;
	}
	
	while(ptrnode->next != NULL )
		ptrnode = ptrnode->next;

	ptrnode->next = node;
	return ptrnode;
	
}

libmenu_node_t *libmenu_pop_node(libmenu_list_t *head)
{
    libmenu_node_t *ptrnode = *head;
    
    if(*head==NULL)
        return NULL; ///there is nothing to pop
    
    //link to next element
    *head = (*head)->next;
    return ptrnode; //remove it
}

void libmenu_show_node(libmenu_node_t *node)
{
    if(node->submenu != NULL)
        printf("%s [+]", node->label);
    else
        printf("%s ", node->label);
    
    return;
}

void libmenu_show_list(libmenu_list_t *head)
{
    libmenu_node_t *ptrnode = *head;
    
    while(ptrnode != NULL)
    {
        libmenu_show_node(ptrnode);
        ptrnode = ptrnode->next;
        putchar('\n');
    }
    
    return;
}

void libmenu_delete_node(libmenu_node_t *node)
{
    if(node == NULL)
        return; //there is nothing to delete
    
    if(node->submenu != NULL)
        libmenu_delete_list(node->submenu);

    if(node->label != NULL)    
        free(node->label);
    free(node);
}

void libmenu_delete_node_s(libmenu_node_t *node)
{
    if(node == NULL)
        return; //there is nothing to delete
    
    if(node->submenu != NULL)
        libmenu_delete_list_s(node->submenu);
    
    node->label = NULL;
    free(node);
}

void libmenu_delete_list(libmenu_list_t *head)
{
    libmenu_node_t *ptrnode;
    
    while(*head != NULL)
    {
        ptrnode = libmenu_pop_node(head);
        libmenu_delete_node(ptrnode);
    }
}

void libmenu_delete_list_s(libmenu_list_t *head)
{
    libmenu_node_t *ptrnode;
    
    while(*head != NULL)
    {
        ptrnode = libmenu_pop_node(head);
        libmenu_delete_node_s(ptrnode);
    }
}

void libmenu_set_trigger(libmenu_node_t *node, void(*f)(void))
{
    node->trigger = f;
}

void libmenu_set_submenu(libmenu_list_t *mainmenu, libmenu_list_t *submenu)
{
    (*mainmenu)->submenu = submenu;
}

