#==============================================================================
# ■ VMDE - gnu.makefile
#==============================================================================

# 这破include居然是根据cwd来的！
include ../inc.makefile

TARGET = libVMDE.so

LDLIBS += /usr/lib/libSOIL.so \
	$(shell pkg-config --libs glfw3 gl glm glew portaudio-2.0 ogg vorbisfile)
LDFLAGS += -shared
CXXFLAGS += -I../lib/SOIL/include -I.. -fPIC \
	$(shell pkg-config --cflags gl glfw3 glm glew portaudio-2.0 vorbisfile)

all:: $(TARGET)
