[=  AutoGen5 Template h=ltstr.h c=ltstr.c =]
[=( dne " *  " "/*  " )=]
 *
 *  Strings that, when written from 'C', must be the same as
 *  the strings typed in the definition and template files.
 */
[=
IF (== (suffix) "h") =][=
  (make-header-guard "ltmain") =]

#include <stdio.h>
#include <options.h>

#ifndef NULL
#  define  NULL  0
#endif
#ifndef NUL
#  define  NUL   '\0'
#endif
#ifndef tSCC
#  define tSCC static const char
#  define tCC  const char
#endif

#ifndef LT_PARAMS
  /* LT_PARAMS is a macro used to wrap function prototypes, so that
     compilers that don't understand ANSI C prototypes still work,
     and ANSI C compilers can issue warnings about type mismatches.  */
#  if defined (__STDC__) || defined (_AIX) || \
              (defined (__mips) && defined (_SYSTYPE_SVR4)) || \
              defined(WIN32) || defined(__cplusplus)
#     define LT_PARAMS(protos)      protos
#     define lt_ptr         void*
#  else
#     define LT_PARAMS(protos)      ()
#     define lt_ptr         char*
#  endif
#endif

#define MODE_CT [=(+ 1 (high-lim "string"))=]
typedef void (emitScriptProc) LT_PARAMS(( int argc, char** argv ));
extern emitScriptProc emitScript;[=
  FOR string=][=
    % call-proc "\nextern emitScriptProc %s;" =][=
  ENDFOR    =]
[=

ELSE  not h suffix

=]#include "[=(. header-file)=]"
[=
(define tpl-name  "")
(define cmd-list  "")
(define cmd-str   "")
(define proc-list "")
(define Cmd-Name  "") =][=

FOR string           =][=

  (set! Cmd-Name (string-capitalize! (get "str_name")))
  (set! cmd-str  (string-append "z" Cmd-Name "Cmd"))

=]
/*
 *  [=(string-upcase! (get "str_name"))=] STRING
 */[=


   IF (exist? "explain")

=]
tSCC zExplain[=(. Cmd-Name)=][ [=
  (+ 1 (len "explain")) =] ] =
[=(kr-string (get "explain"))=];[=
   ENDIF   =][=

   IF (set! tpl-name (string-append (get "str_name") "-txt.tpl"))
      (access? tpl-name R_OK)   =][=

      IF (exist? "explain")     =]

[=    ENDIF                     =]
tSCC [= (. cmd-str)         =][] =[=
   INCLUDE
   (set! cmd-list (string-append cmd-list cmd-str "\n"))
   (out-push-new)
   (. tpl-name)             =][=

   IF (exist? "end-exits") =]
  exit [= end-exits =][=
   ELIF (not (exist? "continues"))  =]
if test -z "${exec_cmd}"
then
  $echo $modename: 'invalid operation mode:  `'$mode\' 1>&2
  $echo 'Try `ltmain --help'\' for more information 1>&2
fi
eval exec $exec_cmd
exit 1[=
    ENDIF =]
[=
   (kr-string (out-pop #t))
   =];

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */[=
   ELIF (exist? "use_cmd")      =][=
      (set! cmd-list (string-append cmd-list "z"
            (string-capitalize! (get "use_cmd")) "Cmd\n"))  =][=
   ELSE  =][=
      (set! cmd-list (string-append cmd-list "(tCC*)NULL\n" )) =][=
   ENDIF =][=

ENDFOR =][=

ENDIF  c/h suffix

=]

[=IF (== (suffix) "h")=]extern [=
  ENDIF=]tCC* apzModeExplain[ MODE_CT ][=
IF (== (suffix) "c") =] = {[=

  FOR string , =]
    [=
    IF   (exist? "use_explain")
          =]zExplain[=(string-capitalize! (get "use_explain"))=][=
    ELIF (exist? "explain")
          =]zExplain[=(string-capitalize! (get "str_name"))=][=
    ELSE  =](tCC*)NULL[=
    ENDIF =][=
  ENDFOR  =]
}[=
ENDIF =];

[=IF (== (suffix) "h")=]extern [=
  ENDIF=]tCC* apz_mode_cmd[   MODE_CT ][=
IF (== (suffix) "c") =] = {
[=(shellf "columns -I4 -S, <<_EOF_\n%s_EOF_" cmd-list) =]
}[=
ENDIF =];

[=IF (== (suffix) "h")=]extern [=
  ENDIF=]emitScriptProc* ap_emitProc[ MODE_CT ][=
IF (== (suffix) "c") =] = {[=

  FOR string , =]
    [=?% call-proc "%s" emitScript=][=
  ENDFOR  =]
}[=

ENDIF =];

[=IF (== (suffix) "h")=]extern [=
  ENDIF=]tCC* apzModeName[    MODE_CT+1 ][=
IF (== (suffix) "c") =] = { NULL[=

  FOR string =],
    "[=str-name=]"[=
  ENDFOR  =]
}[=

ENDIF =];[=

IF (== (suffix) "h")  =]

#define EXPORT
#ifdef DEBUG
#  define LOCAL
#else
#  define LOCAL static
#endif

extern int signalReceived;
extern int scriptStatus;
[=`
for f in \`egrep -l '^EXPORT ' *.c\`
do
  sed -n '/^EXPORT /,/^{/p' $f
done | \
sed '
  s/EXPORT /extern /
  s/^\\([a-zA-Z0-9_]*\\)(.*/\\1 LT_PARAMS((/
  s/;/,/
  s=,[ \t]*/\\*end-decl.*= ));=
  s/^{//' `=]

#endif /* [=(. header-guard)=] */[=

ENDIF =]
