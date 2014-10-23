EXTRA_DIST= \
	landscape.cfg \
	plugins.cfg \
	resources.cfg

install-data-hook:
	cp {landscape,ogre,plugins,resources}.cfg $(DESTDIR)$(bindir)

uninstall-hook:
	rm $(DESTDIR)$(bindir)/{landscape,ogre,plugins,resources}.cfg
