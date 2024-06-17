# LIBRARIES
##################################################
if USE_AXI
lib_LTLIBRARIES += plugins/axidmx/libolaaxidmx.la

# Plugin description is generated from README.md
built_sources += plugins/axidmx/AxiDmxPluginDescription.h
nodist_plugins_axidmx_libolaaxidmx_la_SOURCES = \
    plugins/axidmx/AxiDmxPluginDescription.h
plugins/axidmx/AxiDmxPluginDescription.h: plugins/axidmx/README.md plugins/axidmx/Makefile.mk plugins/convert_README_to_header.sh
	sh $(top_srcdir)/plugins/convert_README_to_header.sh $(top_srcdir)/plugins/axidmx $(top_builddir)/plugins/axidmx/AxiDmxPluginDescription.h

plugins_axidmx_libolaaxidmx_la_SOURCES = \
    plugins/axidmx/AxiDmxDevice.cpp \
    plugins/axidmx/AxiDmxDevice.h \
    plugins/axidmx/AxiDmxPlugin.cpp \
    plugins/axidmx/AxiDmxPlugin.h \
    plugins/axidmx/AxiDmxPort.h \
    plugins/axidmx/AxiDmxThread.cpp \
    plugins/axidmx/AxiDmxThread.h \
    plugins/axidmx/AxiWidget.cpp \
    plugins/axidmx/AxiWidget.h
plugins_axidmx_libolaaxidmx_la_LIBADD = \
    common/libolacommon.la \
    olad/plugin_api/libolaserverplugininterface.la
endif

EXTRA_DIST += plugins/axidmx/README.md
