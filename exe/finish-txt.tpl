[++ AutoGen5 Template ++]
    libdirs="$nonopt"
    admincmds=

    if test -n "$finish_cmds$finish_eval" && test -n "$libdirs"; then
      for dir
      do
	libdirs="$libdirs $dir"
      done

      for libdir in $libdirs; do
	if test -n "$finish_cmds"; then
	  # Do each command in the finish commands.
	  eval cmds=\"$finish_cmds\"
	  save_ifs="$IFS"; IFS='~'
	  for cmd in $cmds; do
	    IFS="$save_ifs"
	    $show "$cmd"
	    $run eval "$cmd" || admincmds="$admincmds
       $cmd"
	  done
	  IFS="$save_ifs"
	fi
	if test -n "$finish_eval"; then
	  # Do the single finish_eval.
	  eval cmds=\"$finish_eval\"
	  $run eval "$cmds" || admincmds="$admincmds
       $cmds"
	fi
      done
    fi

    # Exit here if they wanted silent mode.
    test "$show" = : && exit 0

    echo "----------------------------------------------------------------------"
    echo "Libraries have been installed in:"
    for libdir in $libdirs; do
      echo "   $libdir"
    done
    echo
    echo "If you ever happen to want to link against installed libraries"
    echo "in a given directory, LIBDIR, you must either use libtool, and"
    echo "specify the full pathname of the library, or use the \`-LLIBDIR'"
    echo "flag during linking and do at least one of the following:"
    if test -n "$shlibpath_var"; then
      echo "   - add LIBDIR to the \`$shlibpath_var' environment variable"
      echo "     during execution"
    fi
    if test -n "$runpath_var"; then
      echo "   - add LIBDIR to the \`$runpath_var' environment variable"
      echo "     during linking"
    fi
    if test -n "$hardcode_libdir_flag_spec"; then
      libdir=LIBDIR
      eval flag=\"$hardcode_libdir_flag_spec\"

      echo "   - use the \`$flag' linker flag"
    fi
    if test -n "$admincmds"; then
      echo "   - have your system administrator run these commands:$admincmds"
    fi
    if test -f /etc/ld.so.conf; then
      echo "   - have your system administrator add LIBDIR to \`/etc/ld.so.conf'"
    fi
    echo
    echo "See any operating system documentation about shared libraries for"
    echo "more information, such as the ld(1) and ld.so(8) manual pages."
    echo "----------------------------------------------------------------------"
