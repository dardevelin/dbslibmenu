CC=gcc
CFLAGS=-Wall -Werror -std=c99 -pedantic
#LDFLAGS=
EXECUTABLE=iglibmenuface
SOURCES=main.c libmenu_linked_list.c libmenu_menu_interface.c
OBJECTS=$(SOURCES:.c=.o) 
#CLEAN: $(EXECUTABLE)
	#rm $(OBJECTS)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)
	
$(OBJECTS): $(SOURCES)
	$(CC) $(CFLAGS) -c $(SOURCES) 
