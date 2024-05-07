# Makefile for ecs36b S2024
#

CC = g++ -std=c++14
CFLAGS = -g -I/usr/include/jsoncpp

# CFLAGS = -g -D_ECS35B_DEBUG_ -I/usr/include/jsoncpp
# CFLAGS = -g -Wall -Wstrict-prototypes
# CFLAGS = -O3

LDFLAGS = 	-L/opt/homebrew/lib					\
		-ljsoncpp -lmicrohttpd -ljsonrpccpp-common		\
		-ljsonrpccpp-server -lcurl -ljsonrpccpp-client 

CORE_INCS =	Core.h Person.h Post.h Comment.h Reaction.h		\
		Action.h Link.h JvTime.h Tag.h Thing.h			\
		Record.h GPS.h Labeled_GPS.h Commutable.h Team.h	\
		Holdable.h Locatable.h Message.h OKey.h			\
		Timed_Location.h ecs36b_Common.h ecs36b_Exception.h

CORE_OBJS =	Core.o Person.o Post.o Comment.o Reaction.o		\
	 	Action.o Link.o JvTime.o Tag.o Thing.o OKey.o		\
		Record.o GPS.o Labeled_GPS.o Commutable.o Team.o	\
		Holdable.o Locatable.o ecs36b_JSON.o Message.o		\
		Timed_Location.o ecs36b_Exception.o

# rules.
all: 	ecs36bserver ecs36bupdate ecs36bsearch ecs36b_hw2_ref		\
	ecs36b_hw3_ref_01 hw3ref2client hw3ref2server

#
#

hw3ref2client.h:	ecs36b_s2024_hw3ref2.json
	jsonrpcstub ecs36b_s2024_hw3ref2.json --cpp-server=hw3ref2Server --cpp-client=hw3ref2Client

hw3ref2server.h:		ecs36b_s2024_hw3ref2.json
	jsonrpcstub ecs36b_s2024_hw3ref2.json --cpp-server=hw3ref2Server --cpp-client=hw3ref2Client

ecs36bclient.h:		ecs36b_s2024.json
	jsonrpcstub ecs36b_s2024.json --cpp-server=ecs36bServer --cpp-client=ecs36bClient

ecs36bserver.h:		ecs36b_s2024.json
	jsonrpcstub ecs36b_s2024.json --cpp-server=ecs36bServer --cpp-client=ecs36bClient

ecs36b_hw2_ref.o:	ecs36b_hw2_ref.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) ecs36b_hw2_ref.cpp

ecs36b_hw3_ref_01.o:	ecs36b_hw3_ref_01.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) ecs36b_hw3_ref_01.cpp

hw3ref2client.o:	hw3ref2client.cpp hw3ref2client.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) hw3ref2client.cpp

hw3ref2server.o:	hw3ref2server.cpp hw3ref2server.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) hw3ref2server.cpp

ecs36bupdate.o:		ecs36bupdate.cpp ecs36bclient.h ecs36bserver.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) ecs36bupdate.cpp

ecs36bsearch.o:		ecs36bsearch.cpp ecs36bclient.h ecs36bserver.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) ecs36bsearch.cpp

ecs36bserver.o:		ecs36bserver.cpp ecs36bclient.h ecs36bserver.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) ecs36bserver.cpp

ecs36b_JSON.o:		ecs36b_JSON.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) ecs36b_JSON.cpp

ecs36b_Exception.o:	ecs36b_Exception.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) ecs36b_Exception.cpp

Core.o:			Core.cpp Core.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Core.cpp

OKey.o:			OKey.cpp OKey.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) OKey.cpp

Message.o:		Message.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) Message.cpp

Commutable.o:		Commutable.cpp Commutable.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Commutable.cpp

Transaction.o:		Transaction.cpp Transaction.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Transaction.cpp

Timed_Location.o:	Timed_Location.cpp Timed_Location.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Timed_Location.cpp

Record.o:		Record.cpp Record.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Record.cpp

Tag.o:			Tag.cpp Tag.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Tag.cpp

Team.o:			Team.cpp Team.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Team.cpp

Thing.o:		Thing.cpp Thing.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Thing.cpp

Locatable.o:		Locatable.cpp Locatable.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Locatable.cpp

Holdable.o:		Holdable.cpp Holdable.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Holdable.cpp

GPS.o:			GPS.cpp GPS.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) GPS.cpp

Labeled_GPS.o:		Labeled_GPS.cpp Labeled_GPS.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Labeled_GPS.cpp

Person.o:		Person.cpp Person.h Core.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Person.cpp

Post.o:			Post.cpp Post.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Post.cpp

Comment.o:		Comment.cpp Comment.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Comment.cpp

Reaction.o:		Reaction.cpp Reaction.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Reaction.cpp

JvTime.o:		JvTime.cpp JvTime.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) JvTime.cpp

Link.o:			Link.cpp Link.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Link.cpp

Action.o:		Action.cpp Action.h $(CORE_INCS)
	$(CC) -c $(CFLAGS) Action.cpp

ecs36b_hw2_ref:		$(CORE_OBJS) ecs36b_hw2_ref.o
	$(CC) -o ecs36b_hw2_ref $(CORE_OBJS) ecs36b_hw2_ref.o $(LDFLAGS)

ecs36b_hw3_ref_01:		$(CORE_OBJS) ecs36b_hw3_ref_01.o
	$(CC) -o ecs36b_hw3_ref_01 $(CORE_OBJS) ecs36b_hw3_ref_01.o $(LDFLAGS)

hw3ref2client:		$(CORE_OBJS) hw3ref2client.o
	$(CC) -o hw3ref2client $(CORE_OBJS) hw3ref2client.o $(LDFLAGS)

hw3ref2server:		$(CORE_OBJS) hw3ref2server.o
	$(CC) -o hw3ref2server $(CORE_OBJS) hw3ref2server.o $(LDFLAGS)

ecs36bupdate:		$(CORE_OBJS) ecs36bupdate.o
	$(CC) -o ecs36bupdate $(CORE_OBJS) ecs36bupdate.o $(LDFLAGS)

ecs36bsearch:		$(CORE_OBJS) ecs36bsearch.o
	$(CC) -o ecs36bsearch $(CORE_OBJS) ecs36bsearch.o $(LDFLAGS)

ecs36bserver:		$(CORE_OBJS) ecs36bserver.o
	$(CC) -o ecs36bserver $(CORE_OBJS) ecs36bserver.o $(LDFLAGS)

clean:
	rm -f	*.o *~ core ecs36bserver ecs36bupdate ecs36bsearch	\
	      	ecs36bserver.h ecs36bclient.h 


