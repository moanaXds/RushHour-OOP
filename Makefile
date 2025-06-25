CXX = g++
CXXFLAGS = -g3 -Wall -fmessage-length=0 -std=c++11
OBJS = util.o game.o
LIBS = -lglut -lGLU -lGL -lX11 -lfreeimage -lsfml-audio -lsfml-system -pthread
TARGET = game

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
