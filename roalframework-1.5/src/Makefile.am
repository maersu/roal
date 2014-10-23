INCLUDES = \
	$(STLPORT_CFLAGS) \
	${OGRE_CFLAGS} \
	-I../include \
	-I/usr/include/OGRE \
	-I/usr/include/ode \
	-I/usr/include/OgreOde_Core \
	-I/usr/include/OgreOde_Prefab

lib_LTLIBRARIES=libRoalFramework.la

libRoalFramework_la_SOURCES = \
	World.cpp \
	ValueHandler.cpp \
	Genotype.cpp \
	Phenotype.cpp \
	LeggedCreaturePhenotype.cpp \
	Agent.cpp \
	Brain.cpp \
	Body.cpp \
	Position.cpp \
	BodySegment.cpp \
	CubeSegment.cpp \
	SphereSegment.cpp \
	TriangleMeshSegment.cpp \
	Joint.cpp \
	VehicleSuspensionJoint.cpp \
	AngularMotorJoint.cpp \
	IEffector.cpp \
	IListener.cpp \
	ISensor.cpp \
	KeySensor.cpp \
	NeighborDistanceSensor.cpp \
	UniversalJoint.cpp \
	ImageRenderTarget.cpp \
	HingeJoint.cpp \
	FixedJoint.cpp \
	EyeSegment.cpp \
	BallJoint.cpp \
	MotorJoint.cpp \
	Box.cpp \
	Cage.cpp \
	WorldFrameListener.cpp \
	File.cpp \
	DistributedAgent.cpp \
	Connector.cpp \
	ConnectorMessage.cpp \
	ConnectorMessageTokenizer.cpp \
	ConnectorServerMethod.cpp \
	DistributedWorld.cpp \
	Master.cpp \
	Slave.cpp \
	CreatureFactory.cpp \
	LeggedCreatureBrain.cpp \
	LeggedCreatureGenotype.cpp \
	LeggedCreatureFactory.cpp \
	WheeledCreatureFactory.cpp \
	WheeledCreatureGenotype.cpp \
	MovableText.cpp

libRoalFramework_la_LIBADD = \
	/usr/lib/libOgreOde_Core.la \
	-lOgreMain \
	-lOgrePlatform \
	-lode \
	-lOgreOde_Core \
	-lOgreOde_Prefab
