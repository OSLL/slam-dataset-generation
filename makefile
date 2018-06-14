###### COMPILER ##########
CC := g++ --std=c++11
##########################
###### TESTING ###########
TESTING := test-app
PARAMETERS := res/map.svg
##########################
###### OBJECT FILES ######
# Used to ignore certain directories when finding source files to compile (e.g. for unit tests in packaged with dependencies)
SOURCE_BLACKLIST := svgpp

ALL_COMMON_OBJ := $(foreach file, \
		  $(shell find lib -name "*.cpp"), \
		  $(file:%.cpp=bin/%.o))
COMMON_OBJ := $(strip \
	      $(foreach o, \
	      $(ALL_COMMON_OBJ), \
	      $(if $(strip $(foreach b,$(SOURCE_BLACKLIST),$(findstring $(b),$(o)))),,$(o))))
#########################
###### EXECUTABLES ######
# Used to avoid creating executables from the compiled source of a given folder in src
EXECUTABLE_BLACKLIST := generate_random_bag

EXECUTABLES_UNFILTERED := $(foreach e,$(shell ls -d src/*),$(shell basename $(e)))
EXECUTABLES := $(filter-out $(EXECUTABLE_BLACKLIST),$(EXECUTABLES_UNFILTERED))
#########################
###### INCLUDE FLAGS ####
# Rather expensive option, as with large dependencies, it will include a lot of dirs
#IFLAGS := $(foreach d, \
#	  $(shell find . -type f -name "*.h*" -printf '%h\n' | sort -u), \
#	  -I$(d))

# Cheaper, you just have to specify the full relative path to your header files
IFLAGS := -I./lib -I./lib/svgpp/include -I./lib/svgpp/third_party
#########################

all : $(EXECUTABLES)

# Building executables
define build_executable =
$(eval $(1)_OBJ = $(foreach o, \
		  $(shell find src/$(1)/ -name "*.cpp"), \
		  $(o:%.cpp=bin/%.o)))
$(1) : $(COMMON_OBJ) $($(1)_OBJ)
	$(CC) -o $(1) $($(1)_OBJ) $(COMMON_OBJ)
endef
$(foreach e, $(EXECUTABLES), $(eval $(call build_executable,$e)))

# Compiling translation units
.SECONDEXPANSION:
bin/%.o : %.cpp $$(wildcard $$*.h)
	@if [ ! -d "$(@:%/$(shell basename $@)=%)" ]; \
	then \
		mkdir -p $(@:%/$(shell basename $@)=%); \
	fi;
	$(CC) -c $< -o $@ $(IFLAGS)

# Phony targets
.PHONY : clean test
test : $(TESTING)
	./$(TESTING) $(PARAMETERS)
clean :
	@-rm -rf bin/* $(EXECUTABLES_UNFILTERED) > /dev/null
