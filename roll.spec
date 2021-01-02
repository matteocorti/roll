%define version     2.5.0
%define release     0
%define name        roll
%define sourcename  roll
%define packagename roll

Summary:   A program to roll dices specified in a simple and intuitive way
Name:      %{name}
Version:   %{version}
Release:   %{release}%{?dist}
License:   GPLv2+
Packager:  Joe Klemmer <klemmerj@webtrek.com>
Group:     Amusements/Games
BuildRoot: %{_tmppath}/%{name}-%{version}-root
Source:    https://github.com/matteocorti/%name}/releases/download/v%{version}/%{name}-%{version}.tar.gz
URL:       http://matteocorti.github.io/roll/
BuildRequires: bison, flex

%description
roll is a program to roll dices specified in a simple and intuitive way.

The dices to roll are defined using dN where N is the number of sides. 
Dices can be rolled multiple times by prepending the number of 
repetitions (e.g., 3d6) and used in simple mathematical expressions 
(e.g., 2d8+4).

%prep
%setup

%build
%configure %{_prefix}/usr
%{__make} %{?_smp_mflags}

%install
%{__rm} -rf %{buildroot}
%makeinstall

%clean
%{__rm} -rf %{buildroot}

%files
%{_mandir}/man1/roll.1.gz
%doc AUTHORS ChangeLog NEWS README TODO COPYING VERSION
%attr(0755, root, root) %{_prefix}/bin/roll

%changelog
* Wed Jul  4 2018 Matteo Corti <matteo@corti.li> - 2.2.0-0
- Version 2.2.0

* Tue Aug 23 2016 Matteo Corti <matteo@corti.li> - 2.1.1-0
- Version 2.1.1

* Sat Jun 18 2016 Matteo Corti <matteo@corti.li> - 2.1.0-0
- Version 2.1.0

* Sat Aug 27 2011 Matteo Corti <matteo.corti@id.ethz.ch> - 2.0.0-0
- Version 2

* Thu Mar  1 2007 Matteo Corti <matteo.corti@id.ethz.ch>
- Version is updated by autoconf

* Wed Feb 28 2007 Joe Klemmer <klemmerj@webtrek.com>
- Initial spec file
