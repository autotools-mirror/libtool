[= AutoGen5 Template in=ltmain.in =]
[=

DEFINE test-or-exit

=]if ([=test=]) > /dev/null 2>&1 ; then[=
  invert "  :\nelse"=]
  $echo "$modename: [=msg=]" 1>&2
  $echo "$help" 1>&2
  exit 1
fi[=

ENDDEF  =][=


DEFINE share-to-static-warn

=]
cat 1>&2 <<_EOF_
*** Warning: This library needs some functionality provided by [=libname=].
*** I can automatically link to that library when you link
*** to this library, but I can only do this if you have a shared
*** version of [=libname=].  You do not appear to have one.[=

#  Right here would be a *really* good place to to add some hints
   about where to look to find info about making a shared version ... =]
_EOF_[=

ENDDEF  =]
