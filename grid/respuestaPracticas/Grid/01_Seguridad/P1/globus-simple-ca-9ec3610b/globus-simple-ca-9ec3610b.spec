# This spec file creates a binary RPM that can be used to deploy the CA
# and its related configuration files. The name of the package is based
# on the hash of the CA certificate *on the machine which created the
# CA*. If that was using OpenSSL 0.9.x, it will be different than the
# hash used by OpenSSL 1.x. When this package is built, the hashes are
# set to whichever version of OpenSSL is used on the package build
# machine. Presumably that won't change within a specific OS version.
# This package does not attempt to make this CA the default CA for
# tools like grid-cert-request, but will remove the links to this CA if
# it has been made the default CA by calling grid-default-ca with its
# hash.
%define cadir %{_sysconfdir}/grid-security/certificates

Name: globus-simple-ca-9ec3610b
Version: 1.0
Release: 1%{?dist}
Summary: Simple CA Configuration for /O=Grid/OU=GlobusTest/OU=simpleCA-david.ccgc.mastercpd.upv.es/CN=Globus Simple CA

Group: Development/Tools
License: ASL 2.0
Source: globus_simple_ca_9ec3610b.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root
BuildRequires: openssl
Requires: openssl
BuildArch: noarch

%description
This package contains the CA certificate and related policy files
needed to allow the Globus Toolkit to trust the CA with the subject
name:
"/O=Grid/OU=GlobusTest/OU=simpleCA-david.ccgc.mastercpd.upv.es/CN=Globus Simple CA"
as well as request certificates from that CA.

%prep
%setup -q -n globus-simple-ca-9ec3610b

%build
%define cahash `openssl x509 -noout -hash -in "9ec3610b.0"`
mkdir -m 0755 -p $RPM_BUILD_ROOT/%{cadir}
cp "9ec3610b.0" "$RPM_BUILD_ROOT/%{cadir}/%{cahash}.0"
cp "9ec3610b.signing_policy" "$RPM_BUILD_ROOT/%{cadir}/%{cahash}.signing_policy"
if [ -r "grid-security.conf.9ec3610b" ]; then
    cp "grid-security.conf.9ec3610b" 	        "$RPM_BUILD_ROOT/%{cadir}/grid-security.conf.%{cahash}"
fi
if [ -r "globus-host-ssl.conf.9ec3610b" ]; then
    cp "globus-host-ssl.conf.9ec3610b" "$RPM_BUILD_ROOT/%{cadir}/globus-host-ssl.conf.%{cahash}"
fi
if [ -r "globus-user-ssl.conf.9ec3610b" ]; then
    cp "globus-user-ssl.conf.9ec3610b" "$RPM_BUILD_ROOT/%{cadir}/globus-user-ssl.conf.%{cahash}"
fi
# Save the hash that was used to generate the binary package to a file so that
# we can determine whether we need to remove symlinks during uninstall time.
echo "%{cahash}" > "$RPM_BUILD_ROOT/%{cadir}/9ec3610b.installed_hash"

%clean
rm -rf $RPM_BUILD_ROOT

%preun
installed_hash="$(cat %{cadir}/9ec3610b.installed_hash)"
# Compare file serial numbers to see if the default CA is linked to this one. If so
# remove the links.
if [ -h "%{cadir}/grid-security.conf" ]; then
    if [ "$(ls -H1i "%{cadir}/grid-security.conf" | cut -d' ' -f1)" = 	         "$(ls -H1i "%{cadir}/grid-security.conf.$installed_hash" | cut -d' ' -f1)" ]; then
        rm %{cadir}/grid-security.conf
    fi
fi
if [ -h "%{cadir}/globus-host-ssl.conf" ]; then
    if [ "$(ls -H1i "%{cadir}/globus-host-ssl.conf" | cut -d' ' -f1)" = 	         "$(ls -H1i "%{cadir}/globus-host-ssl.conf.$installed_hash" | cut -d' ' -f1)" ]; then
        rm %{cadir}/globus-host-ssl.conf
    fi
fi
if [ -h "%{cadir}/globus-user-ssl.conf" ]; then
    if [ "$(ls -H1i "%{cadir}/globus-user-ssl.conf" | cut -d' ' -f1)" = 	         "$(ls -H1i "%{cadir}/globus-user-ssl.conf.$installed_hash" | cut -d' ' -f1)" ]; then
        rm %{cadir}/globus-user-ssl.conf
    fi
fi
%files
%defattr(-,root,root,-)
%{_sysconfdir}/grid-security/certificates
