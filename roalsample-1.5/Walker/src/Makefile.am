noinst_PROGRAMS = Walker

INCLUDES = \
	-I../include \
	-I/usr/include \
	-I/usr/include/OGRE \
	-I/usr/include/OgreOde_Core \
	-I/usr/include/OgreOde_Prefab \
	-I/usr/include/RoalFramework \
	-I/usr/include/XmlRpc \
	-I/usr/local/include/RoalFramework

Walker_LDADD = \
	-lOgreMain \
	-lOgrePlatform \
	-lode \
	-lOgreOde_Core \
	-lOgreOde_Prefab \
	-lRoalFramework \
	-lXmlRpcPlusPlus

Walker_LDFLAGS = \
	-L/usr/local/lib \
	-L/usr/lib \
	-L/usr/lib/OGRE

Walker_SOURCES = \
	Walker.cpp \
	WalkerAgent.cpp \
	WalkerBrain.cpp \
	WalkerGenotype.cpp \
	WalkerSuperAgent.cpp \
	WalkerTest.cpp

all:
	mv Walker ../../bin/Walker

clean:
	rm -f ../../bin/Walker

install-exec-local:
	$(INSTALL_PROGRAM) Walker $(DESTDIR)$(bindir)/Walker
