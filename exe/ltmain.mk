
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
	rm -rf .libs lt*.o ltmain libtool $(GENED) *~

ltmain.in : $(TXTTPL) ltstr.def
	autogen -T ltmain.tpl -l ltmacros.tpl -DSCRIPT=1 ltstr.def

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

libtool : ltmain
	./ltmain --mode=link $(CC) -o $@ $(OBJ) -lopts

fwd:
	for f in `egrep -l '^LOCAL ' *.c` ; do \
	( sed '/BEGIN-STATIC-FORWARD/q' $$f ; \
	  sed -n '1,/END-STATIC-FORWARD/d;/^LOCAL /,/^{/p' $$f | \
	  sed 's/^\([a-zA-Z0-9_]*\)(.*/\1 LT_PARAMS((/;\
		s/;/,/;\
		s=,[ \t]*/\*end-decl.*= ));=;\
		s/^{//' ;\
	  echo '/* END-STATIC-FORWARD */';\
	  sed '1,/END-STATIC-FORWARD/d' $$f ) > XXX ; \
	if cmp XXX $$f > /dev/null ; then rm -f XXX ; else mv -f XXX $$f ; fi ; \
	done
