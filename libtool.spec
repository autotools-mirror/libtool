Summary: GNU Libtool - shared library support for source packages
# $Format: "Name: $Project$"$
Name: libtool
# $Format: "Version: $ProjectMajorVersion$"$
Version: 1.2c
Release: 1
Copyright: GPL
Group: Development/Build
Source: ftp://ftp.gnu.org/pub/gnu/libtool-%{PACKAGE_VERSION}.tar.gz
URL: http://www.gnu.org/software/libtool/libtool.html
BuildRoot: /tmp/libtool.root

%description
This is GNU Libtool, a generic library support script.  Libtool hides
the complexity of using shared libraries behind a consistent, portable
interface.

To use libtool, add the new generic library building commands to your
Makefile, Makefile.in, or Makefile.am.  See the documentation for
details.

%prep
%setup

%build
./configure --prefix=/usr
make

%install
rm -rf $RPM_BUILD_ROOT
make install prefix=$RPM_BUILD_ROOT/usr
gzip -9nf $RPM_BUILD_ROOT/usr/info/libtool.info*

%clean
rm -rf $RPM_BUILD_ROOT

%files
%attr(0644, root, root) %doc AUTHORS COPYING ChangeLog NEWS README
%attr(0644, root, root) %doc THANKS TODO doc/PLATFORMS

%attr(0755, root, root) /usr/bin/libtool
%attr(0755, root, root) /usr/bin/libtoolize
%attr(0644, root, root) /usr/info/libtool.info*
%attr(0755, root, root) /usr/share/libtool/config.guess
%attr(0755, root, root) /usr/share/libtool/config.sub
%attr(0755, root, root) /usr/share/libtool/ltconfig
%attr(0644, root, root) /usr/share/libtool/ltmain.sh
%attr(0644, root, root) /usr/share/aclocal/libtool.m4
