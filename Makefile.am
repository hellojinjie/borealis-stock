YFLAGS =
AM_CFLAGS = @CFLAGS@ $(MYFLAGS)
AM_CXXFLAGS = @CXXFLAGS@ $(MYFLAGS)

MAIN = stock

bin_PROGRAMS = $(MAIN)
BOREALIS_SRC = @BOREALISROOT@

LDADD_EXTRAS = -ldl  @BOREALISLIB@  @EXTERNALLIB@

LDADD = -L$(BOREALIS_SRC)/modules/common          -lborealiscommon     \
        -L$(BOREALIS_SRC)/modules/catalog         -lborealiscatalog    \
        -L$(BOREALIS_SRC)/modules/util            -lborealisutil       \
        -L$(BOREALIS_SRC)/modules/ha              -lborealisha         \
        -L$(BOREALIS_SRC)/modules/queryProcessor  -lborealisqp         \
        -L$(BOREALIS_SRC)/external                -lborealisexternal   \
        $(LDADD_EXTRAS)

INCLUDES = @XERCESCINCLUDE@   @NMSTLINCLUDE@                   \
           -I $(BOREALIS_SRC)/modules/common                   \
           -I $(BOREALIS_SRC)/modules/util                     \
           -I $(BOREALIS_SRC)/modules/rpc                      \
           -I $(BOREALIS_SRC)/modules/catalog                  \
           -I $(BOREALIS_SRC)/modules/queryProcessor           \
           -I $(BOREALIS_SRC)/modules/queryProcessor/statsMgr  \
		   -I $(BOREALIS_SRC)/tool/head                                  \
		   -I $(BOREALIS_SRC)/utility/client/rpc

DEPENDENCIES = $(BOREALIS_SRC)/modules/common/libborealiscommon.la

TUPLESOURCE = # InputTuple.h PacketTuple.h

                 ###########################################

stock_DEPENDENCIES = StockMarshal.cc StockMarshal.h

stock_SOURCES = ${TUPLESOURCE} ${stock_DEPENDENCIES}  \
                 stock.cc

${stock_DEPENDENCIES}: stock.xml
	marshal stock.xml

             ###########################################


CLEANFILES = ${stock_DEPENDENCIES}

##############################  end Makefile.am  ###############################
