[++ AutoGen5 Template ++]
[++ IF (getenv "SCRIPT") ++][++ #

NOTE:  -Xcompiler can appear anywhere and the following
argument will be inserted whereever we happen to be in the "base_compile"
variable.  It is not clear what the purpose here is, but if it is supposed
to mark the compiler, then it won't work unless it is the first argument.
If it is the first argument, then it would work anyway.  Therefore, it
seems that the ``-Xcompiler'' is some sort of dinkleberry that could be
simply ignored as a compatibility artifact.  It would render this logic
easier to understand.

++]
    # Get the compilation command and the source file.
    base_compile=
    srcfile="$nonopt"  #  always keep a non-empty value in "srcfile"
    suppress_output=
    arg_mode=normal
    libobj=

    for arg
    do
      case "$arg_mode" in
      arg  )
	# do not "continue".  Instead, add this to base_compile
	lastarg="$arg"
	arg_mode=normal
	;;

      target )
	libobj="$arg"
	arg_mode=normal
	continue
	;;

      normal )
	# Accept any command-line options.
	case $arg in
	-o)
	  if test -n "$libobj" ; then
	    $echo "$modename: you cannot specify \`-o' more than once" 1>&2
	    exit 1
	  fi
	  arg_mode=target
	  continue
	  ;;

	-static)
	  build_old_libs=yes
	  continue
	  ;;

	-prefer-pic)
	  pic_mode=yes
	  continue
	  ;;

	-prefer-non-pic)
	  pic_mode=no
	  continue
	  ;;

	-Xcompiler)
	  arg_mode=arg  #  the next one goes into the "base_compile" arg list
	  continue      #  The current "srcfile" will either be retained or
	  ;;            #  replaced later.  I would guess that would be a bug.

	-Wc,*)
	  args=`$echo "X$arg" | $Xsed -e "s/^-Wc,//"`
	  lastarg=
	  save_ifs="$IFS"; IFS=','
	  for arg in $args; do
	    IFS="$save_ifs"

	    # Double-quote args containing other shell metacharacters.
	    # Many Bourne shells cannot handle close brackets correctly
	    # in scan sets, so we specify it separately.
	    case $arg in
	      *[\[\~\#\^\&\*\(\)\{\}\|\;\<\>\?\'\ \	]*|*]*|"")
	      arg="\"$arg\""
	      ;;
	    esac
	    lastarg="$lastarg $arg"
	  done
	  IFS="$save_ifs"
	  lastarg=`$echo "X$lastarg" | $Xsed -e "s/^ //"`

	  # Add the arguments to base_compile.
	  base_compile="$base_compile $lastarg"
	  continue
	  ;;

	* )
	  # Accept the current argument as the source file.
	  # The previous "srcfile" becomes the current argument.
	  #
	  lastarg="$srcfile"
	  srcfile="$arg"
	  ;;
	esac  #  case $arg
	;;
      esac    #  case $arg_mode

      # Aesthetically quote the previous argument.
      lastarg=`$echo "X$lastarg" | $Xsed -e "$sed_quote_subst"`

      case $lastarg in
      # Double-quote args containing other shell metacharacters.
      # Many Bourne shells cannot handle close brackets correctly
      # in scan sets, so we specify it separately.
      *[\[\~\#\^\&\*\(\)\{\}\|\;\<\>\?\'\ \	]*|*]*|"")
	lastarg="\"$lastarg\""
	;;
      esac

      base_compile="$base_compile $lastarg"
    done # for arg

    case $arg_mode in
    arg)
      $echo "$modename: you must specify an argument for -Xcompile"
      exit 1
      ;;
    target)
      $echo "$modename: you must specify a target with \`-o'" 1>&2
      exit 1
      ;;
    *)
      # Get the name of the library object.
      [ -z "$libobj" ] && libobj=`$echo "X$srcfile" | $Xsed -e 's%^.*/%%'`
      ;;
    esac

[++ ENDIF (getenv "SCRIPT") ++]
    # Recognize several different file suffixes.
    # If the user specifies -o file.o, it is replaced with file.lo
    xform='[cCFSifmso]'
    case $libobj in
    *.ada) xform=ada ;;
    *.adb) xform=adb ;;
    *.ads) xform=ads ;;
    *.asm) xform=asm ;;
    *.c++) xform=c++ ;;
    *.cc) xform=cc ;;
    *.ii) xform=ii ;;
    *.class) xform=class ;;
    *.cpp) xform=cpp ;;
    *.cxx) xform=cxx ;;
    *.f90) xform=f90 ;;
    *.for) xform=for ;;
    *.java) xform=java ;;
    esac

    libobj=`$echo "X$libobj" | $Xsed -e "s/\.$xform$/.lo/"`

    case $libobj in
    *.lo) obj=`$echo "X$libobj" | $Xsed -e "$lo2o"` ;;
    *)[++
      test-or-exit no_help = true
          msg = "cannot determine name of library object from \\`$libobj'"++]
      ;;
    esac

    # Infer tagged configuration to use if any are available and
    # if one wasn't chosen via the "--tag" command line option.
    # Only attempt this if the compiler in the base compile
    # command doesn't match the default compiler.
    if test -n "$available_tags" && test -z "$tagname"; then
      case "$base_compile " in
      "$CC "*) ;;
      # Blanks in the command may have been stripped by the calling shell,
      # but not from the CC environment variable when ltconfig was run.
      "`$echo $CC` "*) ;;
      *)
	for z in $available_tags; do
	  if grep "^# ### BEGIN LIBTOOL TAG CONFIG: $z$" < "$0" > /dev/null; then
	    # Evaluate the configuration.
	    eval "`${SED} -n -e '/^# ### BEGIN LIBTOOL TAG CONFIG: '$z'$/,/^# ### END LIBTOOL TAG CONFIG: '$z'$/p' < $0`"
	    case "$base_compile " in
	    "$CC "*)
	      # The compiler in the base compile command matches
	      # the one in the tagged configuration.
	      # Assume this is the tagged configuration we want.
	      tagname=$z
	      break
	      ;;
	    "`$echo $CC` "*)
	      tagname=$z
	      break
	      ;;
	    esac
	  fi
	done
	# If $tagname still isn't set, then no tagged configuration
	# was found and let the user know that the "--tag" command
	# line option must be used.[++
        test-or-exit test = 'test -z "$tagname"'  no_help = true
msg = "unable to infer tagged configuration\nspecify a tag with \\`--tag'"++]
#        echo "$modename: using $tagname tagged configuration"
	;;
      esac
    fi

    objname=`$echo "X$obj" | $Xsed -e 's%^.*/%%'`
    xdir=`$echo "X$obj" | $Xsed -e 's%/[^/]*$%%'`
    if test "X$xdir" = "X$obj"; then
      xdir=
    else
      xdir=$xdir/
    fi
    lobj=${xdir}$objdir/$objname[++
    test-or-exit test = 'test -z "$base_compile"'
       msg = "you must specify a compilation command" ++]

    # Delete any leftover library objects.
    if test "$build_old_libs" = yes; then
      removelist="$obj $lobj $libobj ${libobj}T"
    else
      removelist="$lobj $libobj ${libobj}T"
    fi

    $run $rm $removelist
    trap "$run $rm $removelist; exit 1" 1 2 15

    # On Cygwin there's no "real" PIC flag so we must build both object types
    case $host_os in
    cygwin* | mingw* | pw32* | os2*)
      pic_mode=default
      ;;
    esac
    if test "$pic_mode" = no && test "$deplibs_check_method" != pass_all; then
      # non-PIC code in shared libraries is not supported
      pic_mode=default
    fi

    # Calculate the filename of the output object if compiler does
    # not support -o with -c
    if test "$compiler_c_o" = no; then
      output_obj=`$echo "X$srcfile" | $Xsed -e 's%^.*/%%' -e 's%\.[^.]*$%%'`.${objext}
      lockfile="$output_obj.lock"
      removelist="$removelist $output_obj $lockfile"
      trap "$run $rm $removelist; exit 1" 1 2 15
    else
      output_obj=
      need_locks=no
      lockfile=
    fi

    # Lock this critical section if it is needed
    # We use this script file to make the link, it avoids creating a new file
    if test "$need_locks" = yes; then
      until $run ln "$0" "$lockfile" 2>/dev/null; do
	$show "Waiting for $lockfile to be removed"
	sleep 2
      done
    elif test "$need_locks" = warn; then[++
      lock-conflict test = 'test -f "$lockfile"' ++]
      echo $srcfile > "$lockfile"
    fi

    if test -n "$fix_srcfile_path"; then
      eval srcfile=\"$fix_srcfile_path\"
    fi

    $run $rm "$libobj" "${libobj}T"

    # Create a libtool object file (analogous to a ".la" file),
    # but don't create it if we're doing a dry run.
    test -z "$run" && cat > ${libobj}T <<EOF
# $libobj - a libtool object file
# Generated by $PROGRAM - GNU $PACKAGE $VERSION$TIMESTAMP
#
# Please DO NOT delete this file!
# It is necessary for linking the library.

# Name of the PIC object.
EOF

    # Only build a PIC object if we are building libtool libraries.
    if test "$build_libtool_libs" = yes; then
      # Without this assignment, base_compile gets emptied.
      fbsd_hideous_sh_bug=$base_compile

      if test "$pic_mode" != no; then
	command="$base_compile $srcfile $pic_flag"
      else
	# Don't build PIC code
	command="$base_compile $srcfile"
      fi

      if test ! -d "${xdir}$objdir"; then
	$show "$mkdir ${xdir}$objdir"
	$run $mkdir ${xdir}$objdir
	status=$?
	if test "$status" -ne 0 && test ! -d "${xdir}$objdir"; then
	  exit $status
	fi
      fi

      if test -z "$output_obj"; then
	# Place PIC objects in $objdir
	command="$command -o $lobj"
      fi

      $run $rm "$lobj" "$output_obj"

      $show "$command"
      if $run eval "$command"; then :
      else
	test -n "$output_obj" && $run $rm $removelist
	exit 1
      fi

      if test "$need_locks" = warn &&
	 test "X`cat $lockfile 2>/dev/null`" != "X$srcfile"; then[++
	 lock-conflict ++]
      fi

      # Just move the object if needed, then go on to compile the next one
      if test -n "$output_obj" && test "X$output_obj" != "X$lobj"; then
	$show "$mv $output_obj $lobj"
	if $run $mv $output_obj $lobj; then :
	else
	  error=$?
	  $run $rm $removelist
	  exit $error
	fi
      fi

      # Append the name of the PIC object to the libtool object file.
      test -z "$run" && cat >> ${libobj}T <<EOF
pic_object='$objdir/$objname'

EOF

      # Allow error messages only from the first compilation.
      suppress_output=' >/dev/null 2>&1'
    else
      # No PIC object so indicate it doesn't exist in the libtool
      # object file.
      test -z "$run" && cat >> ${libobj}T <<EOF
pic_object=none

EOF
    fi

    # Only build a position-dependent object if we build old libraries.
    if test "$build_old_libs" = yes; then
      if test "$pic_mode" != yes; then
	# Don't build PIC code
	command="$base_compile $srcfile"
      else
	command="$base_compile $srcfile $pic_flag"
      fi
      if test "$compiler_c_o" = yes; then
	command="$command -o $obj"
      fi

      # Suppress compiler output if we already did a PIC compilation.
      command="$command$suppress_output"
      $run $rm "$obj" "$output_obj"
      $show "$command"
      if $run eval "$command"; then :
      else
	$run $rm $removelist
	exit 1
      fi

      if test "$need_locks" = warn &&
	 test "X`cat $lockfile 2>/dev/null`" != "X$srcfile"; then[++
	 lock-conflict ++]
      fi

      # Just move the object if needed
      if test -n "$output_obj" && test "X$output_obj" != "X$obj"; then
	$show "$mv $output_obj $obj"
	if $run $mv $output_obj $obj; then :
	else
	  error=$?
	  $run $rm $removelist
	  exit $error
	fi
      fi

      # Append the name of the non-PIC object the libtool object file.
      # Only append if the libtool object file exists.
      test -z "$run" && cat >> ${libobj}T <<EOF
# Name of the non-PIC object.
non_pic_object='$objname'

EOF
    else
      # Append the name of the non-PIC object the libtool object file.
      # Only append if the libtool object file exists.
      test -z "$run" && cat >> ${libobj}T <<EOF
# Name of the non-PIC object.
non_pic_object=none

EOF
    fi

    $run $mv "${libobj}T" "${libobj}"

    # Unlock the critical section if it was locked
    if test "$need_locks" != no; then
      $run $rm "$lockfile"
    fi[++ # 

# Local Variables:
# mode:shell-script
# sh-indentation:2
# tab-width:8
# End:

++]
