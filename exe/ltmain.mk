
SRC = ltmain.c ltopts.c ltstr.c ltcompile.c ltversion.c
OBJ = $(SRC:.c=.o)
GENED = ltmain.in ltstr.[ch] ltopts.[ch]
CC    = cc -I/usr/local/include -g

default : ltmain.in

ltmain.o : ltmain.c ltopts.c ltstr.c ltconfig.x
	$(CC) -c -o ltmain.o ltmain.c

ltmain : $(OBJ)
	$(CC) -o ltmain $(OBJ) -lopts

clean :
	rm -f lt*.o ltmain $(GENED) *~

STRDEFS = ltstr.def \
	lt_base.def      lt_clean.def     lt_compile.def   lt_execute.def \
	lt_finish.def    lt_install.def   lt_link.def

ltmain.in : $(STRDEFS) ltmain.tpl
	autogen -T ltmain.tpl ltstr.def

ltopts.c : ltopts.def
	autogen ltopts.def

ltopts.o : ltopts.c
	$(CC) -c -o ltopts.o -I/usr/local/include ltopts.c

ltstr.c : $(STRDEFS) ltstr.tpl
	autogen -T ltstr.tpl ltstr.def

gen : ltmain.in ltstr.c ltopts.c

zip :
	@ [ -f ltmain ] && mv -f ltmain ltmain.sav ; \
	mkdir ltmain ; \
	cp -fp *.def *.tpl ltmain.c ltmain.mk ltmain/
	tar cvf - ltmain | gzip --best > ltmain.tgz
	@ rm -rf ltmain ; \
	if [ -f ltmain.sav ] ; then mv -f ltmain.sav ltmain ; fi
