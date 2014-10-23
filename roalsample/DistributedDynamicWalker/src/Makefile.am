noinst_PROGRAMS = DDWalkerMaster DDWalkerSlave

INCLUDES = \
	-I../include \
	-I/usr/include \
	-I/usr/include/OGRE \
	-I/usr/include/OgreOde_Core \
	-I/usr/include/OgreOde_Prefab \
	-I/usr/include/XmlRpc \
	-I/usr/include/RoalFramework \
	-I/usr/local/include/RoalFramework

DDWalkerMaster_LDFLAGS = \
	-L/usr/local/lib \
	-L/usr/lib

DDWalkerMaster_LDADD = \
	$(OGRE_LIBS) \
	-lOgreOde_Core \
	-lOgreOde_Prefab \
	-lRoalFramework \
	-lXmlRpcPlusPlus
	
DDWalkerMaster_SOURCES = \
	DDWalkerMasterMain.cpp \
	DDWalkerMaster.cpp

DDWalkerSlave_LDFLAGS = \
	-L/usr/local/lib \
	-L/usr/lib

DDWalkerSlave_LDADD = \
	$(OGRE_LIBS) \
	-lOgreOde_Core \
	-lOgreOde_Prefab \
	-lRoalFramework \
	-lXmlRpcPlusPlus

DDWalkerSlave_SOURCES = \
	DDWalkerSlaveMain.cpp \
	DDWalkerAgent.cpp


all:
	mv {DDWalkerMaster,DDWalkerSlave} ../../bin/

clean:
	rm -f ../../bin/{DDWalkerMaster}

install-exec-local:
	$(INSTALL_PROGRAM) DDWalkerMaster $(DESTDIR)$(bindir)/DDWalkerMaster
	$(INSTALL_PROGRAM) DDWalkerSlave $(DESTDIR)$(bindir)/DDWalkerSlave
