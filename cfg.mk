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
VC_LIST_ALWAYS_EXCLUDE_REGEX = ^mail/

local-checks-to-fix =				\
	sc_prohibit_always-defined_macros	\
	sc_prohibit_always_true_header_tests	\
	sc_require_config_h			\
	sc_require_config_h_first

local-checks-to-skip =				\
	$(local-checks-to-fix)			\
	sc_GPL_version				\
	sc_cast_of_x_alloc_return_value		\
	sc_trailing_blank			\
	sc_unmarked_diagnostics

# GPL_version: checks for GPLv3, which we don't use
# cast_of_x_alloc_return_value:
#         We support C++ compilation which does require casting here.
# trailing_blank: flags valid rfc3676 separators
# unmarked_diagnostics: libtool isn't internationalized

sc_trailing_blank-non-rfc3676:
	@prohibit='([^-][^-][	 ][	 ]*|^[	 ][	 ]*)$$'		\
	halt='found trailing blank(s)'					\
	  $(_sc_search_regexp)

# List syntax-check exempted files.
exclude_file_name_regexp--sc_bindtextdomain = ^tests/.*demo[0-9]*/.*\.c$$
exclude_file_name_regexp--sc_error_message_uppercase = \
  ^$(_build-aux)/cvsu$$
exclude_file_name_regexp--sc_program_name = ^tests/.*demo[0-9]*/.*\.c$$
exclude_file_name_regexp--sc_prohibit_strcmp = \
  ^(doc/libtool.texi|tests/.*demo/.*\.c)$$
exclude_file_name_regexp--sc_prohibit_test_minus_ao = \
  ^m4/libtool.m4$$
exclude_file_name_regexp--sc_space_tab = \.diff$$
exclude_file_name_regexp--sc_trailing_blank-non-rfc3676 = \.diff$$
