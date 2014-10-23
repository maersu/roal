noinst_PROGRAMS = WalkerMaster WalkerSlave NNWalkerSlave

INCLUDES = \
	-I../include \
	-I/usr/include \
	-I/usr/include/OGRE \
	-I/usr/include/OgreOde_Core \
	-I/usr/include/OgreOde_Prefab \
	-I/usr/include/XmlRpc \
	-I/usr/include/RoalFramework \
	-I/usr/local/include/RoalFramework

WalkerMaster_LDFLAGS = \
	-L/usr/local/lib \
	-L/usr/lib

WalkerMaster_LDADD = \
	$(OGRE_LIBS) \
	-lOgreOde_Core \
	-lOgreOde_Prefab \
	-lRoalFramework \
	-lXmlRpcPlusPlus
	
WalkerMaster_SOURCES = \
	WalkerMasterMain.cpp \
	WalkerMaster.cpp

WalkerSlave_LDFLAGS = \
	-L/usr/local/lib \
	-L/usr/lib

WalkerSlave_LDADD = \
	$(OGRE_LIBS) \
	-lOgreOde_Core \
	-lOgreOde_Prefab \
	-lRoalFramework \
	-lXmlRpcPlusPlus

WalkerSlave_SOURCES = \
	WalkerSlaveMain.cpp \
	DistributedWalkerAgent.cpp

NNWalkerSlave_LDFLAGS = \
	-L/usr/local/lib \
	-L/usr/lib

NNWalkerSlave_LDADD = \
	$(OGRE_LIBS) \
	-lOgreOde_Core \
	-lOgreOde_Prefab \
	-lRoalFramework \
	-lXmlRpcPlusPlus \
	-lfann

NNWalkerSlave_SOURCES = \
	NNWalkerSlaveMain.cpp \
	NNWalkerAgent.cpp

all:
	mv {WalkerMaster,WalkerSlave,NNWalkerSlave} ../../../bin/

clean:
	rm -f ../../../bin/{WalkerMaster,WalkerSlave,NNWalkerSlave}

install-exec-local:
	$(INSTALL_PROGRAM) WalkerMaster $(DESTDIR)$(bindir)/WalkerMaster
	$(INSTALL_PROGRAM) WalkerSlave $(DESTDIR)$(bindir)/WalkerSlave
	$(INSTALL_PROGRAM) NNWalkerSlave $(DESTDIR)$(bindir)/NNWalkerSlave
