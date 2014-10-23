SUBDIRS = Walker Distributed Braitenberg media cfg docs DistributedDynamicWalker

dist dist-all: distdir
	tardir=$(distdir) && $(am__tar) | GZIP=$(GZIP_ENV) gzip -c >$(distdir)-src.tar.gz
	tardir=$(distdir) && $(am__tar) | bzip2 -9 -c >$(distdir)-src.tar.bz2
	$(am__remove_distdir)

install-data-hook:
	mkdir -p $(DESTDIR)$(datadir)/RoalSample && \
	cp -r media $(DESTDIR)$(datadir)/RoalSample/media

uninstall-hook:
	rm -rf $(DESTDIR)$(datadir)/RoalSample

doxygen:
	cd docs/doxygen/ && \
	doxygen

html: doxygen

pdf: doxygen
	cd docs/doxygen/latex && \
	make && \
	dvipdf refman.dvi
