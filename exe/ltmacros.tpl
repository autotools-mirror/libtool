[= AutoGen5 Template in=ltmain.in =]
[=

DEFINE test-or-exit

=][=

  #  if there is no test, then just a message and exit
  =][=

  IF (exist? "test")  =]
if ([=test=]) > /dev/null 2>&1 ; then[=
  invert "  :\nelse"  =][=
  ENDIF               =]
  $echo "$modename: [=msg=]" 1>&2[=
  IF (not (exist? "no_help")) =]
  $echo "$help" 1>&2[=
  ENDIF               =]
  exit 1[=
  test "\nfi"         =][=

ENDDEF                =][=


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

ENDDEF                =][=


DEFINE lock-conflict  =][=

  (if (exist? "test")
      (sprintf "\nif (%s) > /dev/null 2>&1 ; then" (get "test"))) =]
  cat >&2 <<_EOF_
*** ERROR, $lockfile exists and contains:
`cat $lockfile 2>/dev/null`

but it should contain:
$srcfile

This indicates that another process is trying to use the same temporary
object file, and libtool could not work around it because your compiler
does not support \\`-c' and \\`-o' together.  If you repeat this
compilation, it may succeed, by chance, but you had better avoid parallel
builds (make -j) on this platform, or get another compiler.
_EOF_
  $run $rm $removelist
  exit 1[=
test "\nfi" =][=

ENDDEF      =]
