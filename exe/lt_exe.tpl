[= AutoGen5 Template =]
  execute)
    modename="$modename: execute"

    # The first argument is the command name.
    cmd="$nonopt"
    [= test-or-exit test = 'test -z "$cmd"'
       msg  = "you must specify a COMMAND" =]
[=(shellf "cat > .lttmp.exe <<'END_LTEXE_TEMP'
[+ AutoGen5 Template +]
%s\nEND_LTEXE_TEMP"
          (get "string[EXECUTE_STRING].text")) =][=
    INCLUDE ".lttmp.exe" =][=
    `rm -f .lttmp.exe`   =]
    ;;
