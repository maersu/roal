AC_INIT([RoalSample], [1.0.0])
AM_INIT_AUTOMAKE([RoalSample], [1.0.0])

AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([dist-bzip2])

AC_PROG_CXX
AC_PROG_LIBTOOL

AC_DEFINE(EXT_HASH,, Use old STL hash options)
AC_DEFINE(GCC_3_1,, 3.x GCC version)
AC_SUBST(OGRE_CFLAGS, "-DEXT_HASH")

CXXFLAGS="$CXXFLAGS $OGRE_CFLAGS"
LDFLAGS="$LDFLAGS $OGRE_LIBS"

AC_SUBST(CXXFLAGS, "$CXXFLAGS")
AC_SUBST(LDFLAGS, "$LDFLAGS")

AC_CONFIG_FILES([ \
	Makefile \
	Walker/Makefile \
	Walker/src/Makefile \
	Walker/include/Makefile \
	Distributed/Makefile \
	Distributed/DistributedWalker/Makefile \
	Distributed/DistributedWalker/src/Makefile \
	Distributed/DistributedWalker/include/Makefile \
	DistributedDynamicWalker/Makefile \
	DistributedDynamicWalker/include/Makefile \
	DistributedDynamicWalker/src/Makefile \
	Braitenberg/Makefile \
	Braitenberg/src/Makefile \
	Braitenberg/include/Makefile \
	media/Makefile \
	cfg/Makefile \
	docs/Makefile \
	docs/doxygen/Makefile \
	docs/doxygen/img/Makefile
])

AC_OUTPUT
