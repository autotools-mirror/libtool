#! /bin/sh

# Unit test helper.
#
# Copyright (C) 2015 Free Software Foundation, Inc.
# This file is part of the GNUlib Library.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.  */


# This shell snippet (when sourced) tries to find as many /bin/sh compatible
# shells as possible on tested box -- and then re-executes the calling script
# in all of them.  At the end, the default shell (/bin/sh usually) is also
# tested.
#
# To write compatible test-case, you usually need only those lines:
#
#   #! /bin/sh
#
#   all_shells_script=$0
#   . "$abs_srcdir/test-all-shells.sh"
#
#   your_check && all_shells_error "failed your_check"
#
#   $all_shells_exit_cmd


# List of shells we try to check in.
: ${GL_ALL_SHELLS='ash bash dash ksh zsh busybox'}

# List of directories to search for the shell interpreter.
: ${GL_ALL_SHELLS_DIRS='/bin /sbin'}

# List of shell emulations to test with BusyBox.
: ${GL_ALL_SHELLS_BBE='sh ash'}

. "$abs_aux_dir"/funclib.sh || exit 1

all_shells_exit_cmd=:

: ${all_shells_script=false}


all_shells_error ()
{
    $ECHO "error: $*" >&2
    all_shells_exit_cmd=false
}


__notify_shell ()
{
    $ECHO "== running in '$*' ==" >&2
}


__reexec_in_all_shells ()
{
    for _G_dir in $GL_ALL_SHELLS_DIRS
    do
      for _G_shell in $GL_ALL_SHELLS
      do
        _G_abs_shell=$_G_dir/$_G_shell
        test -f "$_G_abs_shell" || continue

        case $_G_abs_shell in
          *busybox)
            for _G_bbe in $GL_ALL_SHELLS_BBE
            do
              _G_full_bb="$_G_abs_shell $_G_bbe"
              __notify_shell "$_G_full_bb"
              __GL_ALL_SHELLS_SHELL="$_G_full_bb" \
              "$_G_abs_shell" "$_G_bbe" "$all_shells_script" ${1+"$@"} \
                  || all_shells_error "can't run in $_G_bbe"
            done
            ;;
          *)
            __notify_shell "$_G_abs_shell"
            __GL_ALL_SHELLS_SHELL="$_G_abs_shell" \
            "$_G_abs_shell" "$all_shells_script" ${1+"$@"} \
                || all_shells_error "can't run in $_G_abs_shell"
            ;;
        esac
      done
    done
}


test x = "x$__GL_ALL_SHELLS_SHELL" \
    && __reexec_in_all_shells ${1+"$@"} \
    && __notify_shell "default shell"

:
