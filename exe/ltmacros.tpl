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
  $echo [=(shell-str (prefix "$modename: " (get "msg")))=] 1>&2[=
  IF (not (exist? "no_help")) =]
  $echo "$help" 1>&2[=
  ENDIF               =]
  exit 1[=
  test "\nfi"         =][=

ENDDEF                =][=


DEFINE share-to-static-warn

=]
( echo "*** Warning: Trying to link with static lib archive [=
       libname=]."
  echo "*** I have the capability to link that library automatically when"
  echo "*** you link to this library, but only if you have a shared"
  echo "*** version of [=libname=].  You do not appear to have one."[=

#  Right here would be a *really* good place to to add some hints
   about where to look to find info about making a shared version ... =][=

  IF (exist? "msg") =]
  $echo [=(shell-str (prefix "*** " (get "msg")))=][=
  ENDIF =]
) 1>&2[=

ENDDEF                =][=


DEFINE lock-conflict  =][=

  % test "\nif (%s) > /dev/null 2>&1 ; then" =]
  echo "\
*** ERROR, $lockfile exists and contains:
`cat $lockfile 2>/dev/null`

but it should contain:
  $srcfile

This indicates that another process is trying to use the same temporary
object file, and libtool could not work around it because your compiler
does not support \`-c' and \`-o' together.  If you repeat this
compilation, it may succeed, by chance, but you had better avoid parallel
builds (make -j) on this platform, or get another compiler."

  $run $rm $removelist
  exit 1[=
test "\nfi" =][=

ENDDEF      =]
