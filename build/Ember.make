# GNU Make project makefile autogenerated by Premake

ifndef config
  config=debug_windows
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild prelink

ifeq ($(config),debug_windows)
  RESCOMP = windres
  TARGETDIR = ../bin/Debug-x86_64/Ember
  TARGET = $(TARGETDIR)/Ember.dll
  OBJDIR = ../obj/Debug-x86_64/Ember
  DEFINES += -DBUILD_EMBER_DLL -DER_ASSERTIONS_ENABLED -DDEBUG
  INCLUDES += -I../Ember/src -I../Ember/src/Dependencies/glad/include -I../Ember/src/Dependencies/GLFW/include -I../Ember/src/Dependencies/spdlog/include -I../Ember/src/Dependencies/imgui
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -g
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -g -std=c++11
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lglfw3dll -lSpdlog -lImGui
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -L../Ember/src/Dependencies/GLFW/lib-mingw-w64 -L../Ember/src/Dependencies/spdlog/lib -L../Ember/src/Dependencies/imgui/lib -L/usr/lib64 -m64 -shared -Wl,--out-implib="../bin/Debug-x86_64/Ember/Ember.lib"
  LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running postbuild commands
	cp ../bin/Debug-x86_64/Ember/Ember.dll ../bin/Debug-x86_64/Client
  endef
all: prebuild prelink $(TARGET)
	@:

endif

ifeq ($(config),release_windows)
  RESCOMP = windres
  TARGETDIR = ../bin/Release-x86_64/Ember
  TARGET = $(TARGETDIR)/Ember.dll
  OBJDIR = ../obj/Release-x86_64/Ember
  DEFINES += -DBUILD_EMBER_DLL -DER_ASSERTIONS_ENABLED -DNDEBUG
  INCLUDES += -I../Ember/src -I../Ember/src/Dependencies/glad/include -I../Ember/src/Dependencies/GLFW/include -I../Ember/src/Dependencies/spdlog/include -I../Ember/src/Dependencies/imgui
  FORCE_INCLUDE +=
  ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
  ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -O2
  ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -O2 -std=c++11
  ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
  LIBS += -lglfw3dll -lSpdlog -lImGui
  LDDEPS +=
  ALL_LDFLAGS += $(LDFLAGS) -L../Ember/src/Dependencies/GLFW/lib-mingw-w64 -L../Ember/src/Dependencies/spdlog/lib -L../Ember/src/Dependencies/imgui/lib -L/usr/lib64 -m64 -shared -Wl,--out-implib="../bin/Release-x86_64/Ember/Ember.lib" -s
  LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running postbuild commands
	cp ../bin/Release-x86_64/Ember/Ember.dll ../bin/Release-x86_64/Client
  endef
all: prebuild prelink $(TARGET)
	@:

endif

OBJECTS := \
	$(OBJDIR)/glad.o \
	$(OBJDIR)/EmberApp.o \
	$(OBJDIR)/Layer.o \
	$(OBJDIR)/LayerStack.o \
	$(OBJDIR)/Log.o \
	$(OBJDIR)/Window.o \
	$(OBJDIR)/GuiLayer.o \
	$(OBJDIR)/imgui_impl_opengl3.o \

RESOURCES := \

CUSTOMFILES := \

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

$(TARGET): $(GCH) ${CUSTOMFILES} $(OBJECTS) $(LDDEPS) $(RESOURCES) | $(TARGETDIR)
	@echo Linking Ember
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(CUSTOMFILES): | $(OBJDIR)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning Ember
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) $(PCH) | $(OBJDIR)
$(GCH): $(PCH) | $(OBJDIR)
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
else
$(OBJECTS): | $(OBJDIR)
endif

$(OBJDIR)/glad.o: ../Ember/src/Dependencies/glad/src/glad.c
	@echo $(notdir $<)
	$(SILENT) $(CC) $(ALL_CFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/EmberApp.o: ../Ember/src/Ember/Core/EmberApp.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Layer.o: ../Ember/src/Ember/Core/Layer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/LayerStack.o: ../Ember/src/Ember/Core/LayerStack.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Log.o: ../Ember/src/Ember/Core/Log.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Window.o: ../Ember/src/Ember/Core/Window.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/GuiLayer.o: ../Ember/src/Ember/Gui/GuiLayer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/imgui_impl_opengl3.o: ../Ember/src/Ember/Gui/imgui_impl_opengl3.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(OBJDIR)/$(notdir $(PCH)).d
endif