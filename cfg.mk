# cfg.mk -- Configuration for maintainer-makefile
#
#   Copyright (c) 2011 Free Software Foundation, Inc.
#   Written by Gary V. Vaughan, 2011
#
#   This file is part of GNU Libtool.
#
# GNU Libtool is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# GNU Libtool is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Libtool; see the file COPYING.  If not, a copy
# can be downlodad from http://www.gnu.org/licenses/gpl.html,
# or obtained by writing to the Free Software Foundation, Inc.,
# 51 Franklin Street, Boston, # MA 02111-1301, USA.

# Set format of NEWS
old_NEWS_hash := d41d8cd98f00b204e9800998ecf8427e

manual_title = Portable Dynamic Shared Object Management

# Set the release announcement email addresses, maint.mk will email the
# translation-project instead of autotools-announce otherwise.
ifeq ($(RELEASE_TYPE),stable)
announcement_Cc_ = autotools-announce@gnu.org
else
announcement_Cc_ = autotools-announce@gnu.org, $(PACKAGE_BUGREPORT)
endif

# Don't syntax check the mail subdirectory.
VC_LIST_ALWAYS_EXCLUDE_REGEX = /mail/

local-checks-to-fix =				\
	sc_file_system				\
	sc_m4_quote_check			\
	sc_makefile_TAB_only_indentation	\
	sc_makefile_at_at_check			\
	sc_prohibit_always-defined_macros	\
	sc_prohibit_always_true_header_tests	\
	sc_prohibit_cvs_keyword			\
	sc_prohibit_doubled_word		\
	sc_prohibit_empty_lines_at_EOF		\
	sc_prohibit_have_config_h		\
	sc_prohibit_magic_number_exit		\
	sc_prohibit_stddef_without_use		\
	sc_prohibit_strcmp			\
	sc_prohibit_test_minus_ao		\
	sc_prohibit_undesirable_word_seq	\
	sc_require_config_h			\
	sc_require_config_h_first		\
	sc_space_tab				\
	sc_trailing_blank			\
	sc_unmarked_diagnostics			\
	sc_useless_cpp_parens

local-checks-to-skip =				\
	$(local-checks-to-fix)			\
	sc_GPL_version				\
	sc_avoid_if_before_free			\
	sc_bindtextdomain			\
	sc_cast_of_argument_to_free		\
	sc_cast_of_x_alloc_return_value		\
	sc_error_message_uppercase		\
	sc_program_name

# GPL_version: checks for GPLv3, which we don't use
# avoid_if_before_free: we don't use the gnulib malloc modules
# bindtextdomain: libtool isn't internationalized
# cast_of_argument_to_free: ditto
# cast_of_x_alloc_return_value: ditto
# error_message_uppercase: we like our error messages
# program_name: libtool has no programs!
