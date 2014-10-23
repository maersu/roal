SUBDIRS = src include media docs

dist dist-all: distdir
	tardir=$(distdir) && $(am__tar) | GZIP=$(GZIP_ENV) gzip -c >$(distdir)-src.tar.gz
	tardir=$(distdir) && $(am__tar) | bzip2 -9 -c >$(distdir)-src.tar.bz2
	$(am__remove_distdir)

install-data-hook:
	mkdir -p $(DESTDIR)$(datadir)/RoalFramework && \
	cp -r media $(DESTDIR)$(datadir)/RoalFramework

uninstall-hook:
	rm -rf $(DESTDIR)$(datadir)/RoalFramework

doxygen:
	cd docs/doxygen/ && \
	doxygen

html: doxygen

pdf: doxygen
	cd docs/doxygen/latex && \
	make && \
	latex refman.tex && \
	dvipdf refman.dvi
