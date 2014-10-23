noinst_PROGRAMS = Braitenberg

INCLUDES = \
	-I../include \
	-I/usr/include \
	-I/usr/include/OgreOde_Core \
	-I/usr/include/OgreOde_Prefab \
	-I/usr/include/RoalFramework \
	-I/usr/include/XmlRpc \
	-I/usr/local/include/RoalFramework \
	-I/usr/include/OGRE

Braitenberg_LDADD = \
	$(OGRE_LIBS) \
	-lOgreOde_Core \
	-lOgreOde_Prefab \
	-lRoalFramework \
	-lXmlRpcPlusPlus

Braitenberg_LDFLAGS = \
	-L/usr/local/lib \
	-L/usr/lib

Braitenberg_SOURCES = \
	VictimBraitenbergAgent.cpp \
	HunterBraitenbergAgent.cpp \
	VictimBraitenbergBrain.cpp \
	HunterBraitenbergBrain.cpp \
	Plant.cpp \
	PlantAgent.cpp \
	BraitenbergTest.cpp

all:
	mv Braitenberg ../../bin/Braitenberg

clean:
	rm -f ../../bin/Braitenberg

install-exec-local:
	$(INSTALL_PROGRAM) Braitenberg $(DESTDIR)$(bindir)/Braitenberg
	
	
	
