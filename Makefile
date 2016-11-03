CXX = g++
ECHO = echo
RM = rm -f

# -std=c++11
CXXFLAGS = -Wall -ggdb -funroll-loops
LDFLAGS = -lncurses

BIN = rlg327
OBJS = rlg327.o dungeon.o heap.o utils.o path.o character.o pc.o npc.o \
       move.o event.o io.o MonsterFactory.o MonsterType.o

all: $(BIN) etags

$(BIN): $(OBJS)
	@$(ECHO) Linking $@
	@$(CXX) $^ -o $@ $(LDFLAGS)

-include $(OBJS:.o=.d)


%.o: %.cpp
	@$(ECHO) Compiling $<
	@$(CXX) $(CXXFLAGS) -MMD -MF $*.d -c $<

.PHONY: all clean clobber etags

clean:
	@$(ECHO) Removing all generated files
	@$(RM) *.o $(BIN) *.d TAGS core vgcore.* gmon.out

clobber: clean
	@$(ECHO) Removing backup files
	@$(RM) *~ \#* *pgm

etags:
	@$(ECHO) Updating TAGS
	@etags *.[ch] *.cpp
