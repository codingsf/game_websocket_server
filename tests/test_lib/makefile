#absolute paths are necessary for dependency files to work properly
LIBRARIES = -lpthread -lstdc++ -lm

# we need to use absolute path for dependency files to work properly
PROJECT_DIRECTORY = $(abspath ../../)/

COMP = g++
CFLAGS = -DDEBUG -O0 -g3 -fno-omit-frame-pointer -fno-inline

EXECUTABLE := $(PROJECT_DIRECTORY)$(EXECUTABLE_NAME)
OBJ_DIR := $(PROJECT_DIRECTORY)tests/objs/
DEP_DIR := $(PROJECT_DIRECTORY)tests/deps/
DEP_TEMP := $(DEP_DIR)temp/
HEAD_PATH := $(PROJECT_DIRECTORY)

LIBRARY_NAME = $(OBJ_DIR)test_lib.a

# use the full path of the cpp file in object file names to
# prevent multiple files with the same name in different
# folders from overwriting each other in the /objs folder
# we replace all the / with -!- to get the file name and then
# append it to the path. -!- was chosen because it is unlikely to
# be part of a filename and has no special meaning in make
OBJECT_NAMES = $(subst  /,-!-, $(basename $(abspath $(FILE_LIST))))
OBJECTS = $(addprefix $(OBJ_DIR), $(patsubst %,%.o,$(OBJECT_NAMES)))

#compiler flags for generating dependency file
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_TEMP)$*.Td

# we write our dependencies to a temp folder and then move them into
# the deps folder after they compile successfully. This is done to prevent
# the dependency files from getting corrupted in a failed compile.

# command to move dependencies from the temp folder into the deps folder
MOV_DEPS = mv -f $(DEP_TEMP)$*.Td $(DEP_DIR)$*.d

CXX = $(COMP) -I $(HEAD_PATH) $(CFLAGS) $(DEPFLAGS) -std=c++17

DEPFILES = $(patsubst %,$(DEP_DIR)%.d,$(basename $(notdir $(OBJECTS))))

all: $(LIBRARY_NAME)

$(LIBRARY_NAME): $(OBJECTS)
	gcc-ar rcs $@ $^

# in order for this rule to work filenames cannot contain the
# string -!- or any of the special symbols make uses such as @ or $
# In order to get the .cpp filename we replace all the -!- with /
# This will give us the full path of the file.
.SECONDEXPANSION:
$(OBJ_DIR)%.o: $$(subst  -!-,/, %.cpp) $(DEP_DIR)%.d
	$(CXX) -c -o $@ $<
	$(MOV_DEPS)

.PRECIOUS: $(DEP_DIR)%.d $(CPP_DIR)%.h.gch

$(DEP_DIR)%.d: ;

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f $(DEPFILES)
	rm -f $(LIBRARY_NAME)

-include $(DEPFILES)
