
MTPL =  ltmacros.tpl
TPL  = base-txt.tpl clean-txt.tpl compile-txt.tpl execute-txt.tpl \
       finish-txt.tpl install-txt.tpl link-txt.tpl ltmain.tpl ltstr.tpl
DEF  = ltstr.def

newltmain.in : $(TPL) $(DEF) $(MTPL)
	autogen -T ltmain.tpl -l ltmacros.tpl ltstr.def
