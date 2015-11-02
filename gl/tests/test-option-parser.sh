#! /bin/sh

# Unit tests for funclib.sh
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

all_shells_script=$0
. "$abs_srcdir/test-all-shells.sh"

. "$abs_aux_dir"/options-parser || exit 1

helper=$abs_srcdir/test-option-parser-helper

check_output_inner ()
{
    exp_output=$1 ; shift
    exp_retval=$1 ; shift

    func_quote pretty ${1+"$@"}
    $ECHO "[[ output check ]] args: $func_quote_result"

    output=`$helper ${1+"$@"} 2>/dev/null`
    rc=$?
    test "$rc" -eq "$exp_retval" \
        || all_shells_error "unexpected exit status $rc $exp_retval"

    if test "$exp_output" = "$output"
    then
      :
    else
      $ECHO "expected:"
      $ECHO "$exp_output"
      $ECHO "given:"
      $ECHO "$output"
      all_shells_error "unexpected output"
    fi
}


check_output ()
{
    _co_exp_output=$1 ; shift
    _co_exp_retval=$1 ; shift
    # TODO: check with --debug
    check_output_inner "$_co_exp_output" "$_co_exp_retval" ${1+"$@"}
    check_output_inner "$_co_exp_output" "$_co_exp_retval" --debug ${1+"$@"}
}


check_retval ()
{
    exp_retval=$1 ; shift
    func_quote pretty ${1+"$@"}
    $ECHO "[[ retval check ]] args: $func_quote_result"
    $helper ${1+"$@"} >/dev/null 2>/dev/null
    rc=$?
    test "$rc" -eq "$exp_retval" \
        || all_shells_error "unexpected retval $rc (should be $exp_retval)"
}


grep_output ()
{
    grep_for=$1 ; shift
    exp_retval=$1 ; shift

    func_quote pretty ${1+"$@"}
    $ECHO "[[ grep for '$grep_for' ]] args: $func_quote_result"

    output=`$helper ${1+"$@"} 2>/dev/null`
    rc=$?
    case $output in
      *$grep_for*) : ;;
      *) all_shells_error "$grep_for is not in stdout $output" ;;
    esac

    test "$rc" -eq "$exp_retval" \
        || all_shells_error "unexpected retval $rc (should be $exp_retval)"
}


check_output HELP         0 --help
check_output HELP         0 --test jej --help
check_output HELP         0 --test=jej --help
check_output HELP         0 --test= --help

check_output EMPTY_TEST   0 --test=
check_output EMPTY_TEST   0 -t ''
check_output EMPTY_TEST   0 --test ''
check_output FALSE_TEST   1 --test=false
check_output FALSE_TEST   1 -tfalse
check_output FALSE_TEST   1 -t false
check_output UNSET_TEST   0
check_output 'ONE_ARG a'  0 a
check_output THREE_ARGS   0 a b c
check_output MORE_ARGS    0 a b c d

check_output SHORTCUT     0 short
check_output SHORTCUT     0 shortcut
check_output HELP         0 short --help

check_output eval         4 eval 'echo eval ; exit 4'
check_output eval         4 validate_out eval 'echo eval ; exit 4'

# No argument.
check_retval              1 --test
check_retval              1 --not-existent
check_retval              1 short --not-existent

grep_output  test-version 0 --version
grep_output  test-version 0 --version --whatever
grep_output  test-version 0 --debug --version

# TODO: Shouldn't this code be able to parse multiple occurrences of
# single option (IOW, hooks should be called in loop..)?
# check_output FALSE_TEST 1 short --test false
# check_output FALSE_TEST 1 --test a --test false

$all_shells_exit_cmd
