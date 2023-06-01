all: world

CXX?=g++
CXXFLAGS?=--std=c++23 -Wall -fPIC
LDFLAGS?=-L/lib -L/usr/lib

CXXFLAGS+= -DAPPNAME=speedtest-ubus

INCLUDES+= -I./include
LIBS:=-lubox -lblobmsg_json -lubus -luci -lspeedtestcpp

include common/Makefile.inc
include logger/Makefile.inc
include signal/Makefile.inc

OBJS:= \
	objs/ubus.o objs/ubus_funcs.o \
	objs/loop.o objs/main.o

world: speedtest-ubus

objs/ubus.o: src/ubus.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/ubus_funcs.o: src/ubus_funcs.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/loop.o: src/loop.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

objs/main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

speedtest-ubus: $(COMMON_OBJS) $(LOGGER_OBJS) $(SIGNAL_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -L. $(LIBS) $^ -o $@;

.PHONY: clean
clean:
	rm -f objs/*.o speedtest-ubus
