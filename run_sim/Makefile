OBJDIR := obj

SOURCE :=		../*.cpp \

INCLUDE :=  -I../\
			
vpath %.cpp $(dir $(SOURCE))

OBJS := $(patsubst %.cpp,%.o,$(wildcard $(SOURCE)))

OBJECT := $(addprefix $(OBJDIR)/, $(notdir $(OBJS)))

TARGET := ./simulation

CC := g++

CFLAGS := -g -Wall -m64 -O3 -pthread -std=c++11 $(DEFINES) $(INCLUDE) 
CXXFLAGS := $(CFLAGS) 

.PHONY : everything objs clean veryclean rebuild
everything : $(TARGET)
objs : $(OBJECT)
rebuild : veryclean everything

clean: 
	rm -rf $(OBJDIR)
	rm -rf $(TARGET)


$(TARGET) : $(OBJECT)
	echo $(OBJECT)
	$(CC)  $(CXXFLAGS) -o $@ $(OBJECT) $(LDFLAGS) $(LIBS)

$(OBJECT) : $(OBJDIR)/%.o : %.cpp
	echo $(OBJECT)
	@[ ! -e $(dir $@) ] & mkdir -p $(dir $@)
	$(CC)  $(CXXFLAGS) -o $@ -c $<



