[=  AutoGen5 Template h=ltstr.h c=ltstr.c =]
[=( dne " *  " "/*  " )=]
 *
 *  Strings that, when written from 'C', must be the same as
 *  the strings typed in the definition files.
 */[=

IF (== (suffix) "h") =][=

  (define guard (string-append "HDRGRD_" (string-upcase!
                (string->c-name! (out-name)) )))
  (define hdr-name (out-name)) =]
#ifndef [=(. guard)=]
#define [=(. guard)=] 1

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
[=

ELSE

=]
#include "[=(. hdr-name)=]"
[=

ENDIF =][=

FOR string

=][=

  IF (== (suffix) "c") =]
/*
 *  [=(string-upcase! (get "str_name"))=] STRING
 */[=


    IF (exist? "explain")

=]
tSCC zExplain[=(string-capitalize! (get "str_name"))=][ [=
  (+ 1 (len "explain")) =] ] =
[=(kr-string (get "explain"))=];[=

      IF (exist? "text") =]

[=    ENDIF =][=
    ENDIF   =][=
  ENDIF "c" =][=

  IF (exist? "text")

=][=
    IF (== (suffix) "h") =]
#define [=(string-upcase! (get "str_name"))=]_CMD_SIZE [=(+ 1 (len "text"))=]
extern [=
    ELSE =]
[=  ENDIF
=]tCC z[=(string-capitalize! (get "str_name"))
             =]Cmd[ [=(string-upcase! (get "str_name"))=]_CMD_SIZE ][=
    IF (== (suffix) "c") =] =
[=(kr-string (get "text"))=][=
    ENDIF =];[=

  ENDIF =]
[=
  IF (== (suffix) "c") =]
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */[=
  ENDIF =][=

ENDFOR

=][=

IF (== (suffix) "h")

=]#define MODE_CT [=(+ 1 (high-lim "string"))=]
typedef void (emitScriptProc) LT_PARAMS(( int argc, char** argv ));
extern emitScriptProc emitScript;[=
  FOR string=][=
    % call-proc "\nextern emitScriptProc %s;" =][=
  ENDFOR    =][=
ENDIF =]

[=IF (== (suffix) "h")=]extern [=
  ENDIF=]tCC* apz_mode_explain[ MODE_CT ][=
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
  ENDIF=]tCC* apz_mode_cmd[     MODE_CT ][=
IF (== (suffix) "c") =] = {[=

  FOR string , =]
    [=
    IF   (exist? "use_cmd")
          =]z[=(string-capitalize! (get "use_cmd"))=]Cmd[=
    ELIF (exist? "text")
          =]z[=(string-capitalize! (get "str_name"))=]Cmd[=
    ELSE  =](tCC*)NULL[=
    ENDIF =][=
  ENDFOR  =]
}[=
ENDIF =];

[=IF (== (suffix) "h")=]extern [=
  ENDIF=]emitScriptProc* ap_emitProc[ MODE_CT ][=
IF (== (suffix) "c") =] = {[=

  FOR string , =]
    [=
    IF (or (exist? "use_cmd") (exist? "text"))
          =][=?% call-proc "%s" emitScript=][=
    ELSE  =](emitScriptProc*)NULL[=
    ENDIF =][=
  ENDFOR  =]
};[=

ELSE =];

extern int signalReceived;
extern int scriptStatus;

extern void closeScript     LT_PARAMS(( FILE* fp ));
extern void modalUsage      LT_PARAMS(( tOptions* pOpts, int exitCode ));
extern void emitShellQuoted LT_PARAMS(( tCC* pzArg, FILE* outFp ));
extern void emitShellArg    LT_PARAMS(( tCC* pzArg, FILE* outFp ));

#endif /* [=(. guard)=] */[=

ENDIF =]
