#************************************************************#
#   Makefile
#    history:  2010-09-03 lirui build
#
#************************************************************#

#
INCLUDE =  -I./
LIBS = -L./ -g
SRCPATH = ./

all:IAppManager.so test

test:IAppManager.so main.o AppCallBack_example.o
	g++ -s  main.o AppCallBack_example.o -L./  -ldl  -lIAppManager  -o test

IAppManager.so:IAppManager.o IAppCallBack.o ProtoBuffer.o
	gcc  $(INCLUDE) $(LIBS) -fPIC -shared IAppManager.o IAppCallBack.o ProtoBuffer.o -o libIAppManager.so

IAppManager.o:IAppManager.cpp
	gcc -fPIC $(INCLUDE) $(LIBS) -c IAppManager.cpp

IAppCallBack.o:IAppCallBack.cpp
	gcc -fPIC $(INCLUDE) $(LIBS) -c IAppCallBack.cpp

main.o:main.cpp
	gcc -fPIC $(INCLUDE) $(LIBS) -c main.cpp

AppCallBack_example.o:AppCallBack_example.cpp
	gcc -fPIC $(INCLUDE) $(LIBS) -c AppCallBack_example.cpp

ProtoBuffer.o:ProtoBuffer.cpp
	gcc -fPIC $(INCLUDE) $(LIBS) -c ProtoBuffer.cpp

IJavaCallBack.o:IJavaCallBack.cpp
	gcc -fPIC $(INCLUDE) $(LIBS) -c IJavaCallBack.cpp

clean :
	-rm *.o *.so test
