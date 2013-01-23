version = $(shell grep Version rpm.spec|cut -c 10-)
rpmhome = $(shell cut -c 10- ~/.rpmmacros)

zu: zu.c
	sudo rm -f zu
	gcc zu.c -o zu
	sudo chown zope:zope zu
	sudo chmod u+s zu

clean:
	sudo rm zu

release:
	tar czf $(rpmhome)/SOURCES/zu-$(version).tgz zu.c

rpm: release
	rpmbuild -ba rpm.spec
