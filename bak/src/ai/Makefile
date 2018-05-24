############################################################################################
# 	A template Makefile for OpenBoss ,just simply replace or modify the following items to 
# meet your own requirement.
############################################################################################
DB=1
DEBUG=1
#
# define your destination
PRODDEST=libcurlTool.so

# define your idl path
PRODIDLPATH=

# PRODIDLPATH and PRODDEST must set before this include
include $(OB_REL)/etc/Cmake

# define your definition when build debug
PRODDEBUGDEFS=-DDEBUG

# define your temp file. when you make clean it will be clean.
PRODTMPOBJ=

# define your lib path
PRODLIBPATH=. $(OB_REL)/lib

# define your lib
PRODLIBS=curl_new CbsSysClassD

# define your include path
PRODINCS=	.									\
		$(OB_SRC)/obsystem/include \
		$(OB_REL)/include \

# define your CC option
PRODOPTS=-DTEST

# define rules for compiling an excutable or a share lib,alternatively

Curl_Class_OBJ=curlTool.o c_curl_util.o jsoncpp/src/json/json_value.o jsoncpp/src/json/json_writer.o jsoncpp/src/json/json_reader.o 

libcurlTool.so:$(Curl_Class_OBJ)
	$(SHLD) $^ $(SHLDFLAGS) $(LDOPTS) -L/test11/kfdev/ngcrm/lib_acct -lcurl_new -o $@

# define rules for compiling an excutable or a share lib,alternatively
TEST_OBJ=test.o
test: $(TEST_OBJ)
	$(CXX) $^ $(LDFLAGS) -o $@ -lCbsSysClass$(BUILDTYPE) 

# define install rules
install:$(PRODDEST)
	cp -rf libcurlTool.a $(OB_REL)/lib

install_headers:

install_idl:

NEEDED_MAKEDEP=$(wildcard $(MAKEDEP_FILE))
ifeq ($(NEEDED_MAKEDEP), $(MAKEDEP_FILE))
	include $(MAKEDEP_FILE)
endif

PROD_SRC=$(Curl_Class_OBJ:.o=.cpp)
depend:$(PROD_SRC)
	$(MKDEP) $(CXXFLAGS) $(INCFLAGS) $^ > $(MAKEDEP_FILE)
	$(FILTER_MKDEP)
	
