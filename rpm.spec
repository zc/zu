Name: zu
Version: 0.1
Release: 1

Summary: Become Zope
Group: Applications/Zope
Requires: zcuser-zope

##########################################################################
# Lines below this point normally shouldn't change

%define source %{name}-%{version}

Vendor: Zope Corporation
Packager: Zope Corporation <sales@zope.com>
License: ZPL
AutoReqProv: no
Source: %{source}.tgz
Prefix: /opt
BuildRoot: /tmp/%{name}

%description
%{summary}

%prep
%setup -c

%build
rm -rf %{buildroot}
mkdir %{buildroot} %{buildroot}/opt
cp -r $RPM_BUILD_DIR/%source %{buildroot}/opt/%{name}
cd %{buildroot}/opt/%{name}
gcc -o zu zu.c

%clean
rm -rf %{buildroot}
rm -rf $RPM_BUILD_DIR/%{source}

%posttrans
cp /opt/zu/zu /usr/bin
chown zope:zope /usr/bin/zu
chmod u+s       /usr/bin/zu

%preun
rm /usr/bin/zu

%files
%defattr(-, root, root)
/opt/%{name}
