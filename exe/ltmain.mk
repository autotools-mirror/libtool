
SRC    = ltmain.c ltopts.c ltstr.c ltcompile.c ltexe.c ltversion.c
OBJ    = $(SRC:.c=.o)
GENED  = ltmain.in ltstr.[ch] ltopts.[ch]
CC     = cc -I/usr/local/include -g
TXTTPL = base-txt.tpl clean-txt.tpl compile-txt.tpl execute-txt.tpl \
	finish-txt.tpl install-txt.tpl link-txt.tpl

default : ltmain.in

ltmain.o : ltmain.c ltopts.c ltstr.c ltconfig.x
	$(CC) -c -o ltmain.o ltmain.c

ltmain : $(OBJ)
	$(CC) -o ltmain $(OBJ) -lopts

clean :
	rm -f lt*.o ltmain $(GENED) *~

ltmain.in : $(TXTTPL) ltstr.def
	autogen -T ltmain.tpl -l ltmacros.tpl ltstr.def

ltstr.c : ltstr.def ltstr.tpl ltmacros.tpl
	autogen -T ltstr.tpl -l ltmacros.tpl ltstr.def

ltstr.h : ltstr.c
	@-:

ltopts.c : ltopts.def
	autogen ltopts.def

ltopts.h : ltopts.h
	@-:

ltopts.o : ltopts.c
	$(CC) -c -o ltopts.o -I/usr/local/include ltopts.c

gen : ltmain.in ltstr.c ltopts.c
