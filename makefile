CC := g++ --std=c++11

TESTING := test-app
PARAMETERS := res/map.svg

# Used to temporarily ignore folders in src
EXECUTABLE_BLACKLIST := generate_random_bag

EXECUTABLES_UNFILTERED := $(foreach e,$(shell ls -d src/*),$(shell basename $(e)))
EXECUTABLES := $(filter-out $(EXECUTABLE_BLACKLIST),$(EXECUTABLES_UNFILTERED))


COMMON_OBJ := $(foreach o, \
	      $(shell find lib -name "*.cpp"), \
	      $(o:lib/%.cpp=bin/lib/%.o))

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
IFLAGS := $(foreach d, \
	  $(shell find . -type f -name "*.h*" -printf '%h\n' | sort -u), \
	  -I$(d))
.SECONDEXPANSION:
bin/%.o : %.cpp $$(wildcard $$*.h)
	@if [ ! -d "$(@:%/$(shell basename $@)=%)" ]; \
	then \
		mkdir -p $(@:%/$(shell basename $@)=%); \
	fi;
	$(CC) -c $< $(IFLAGS) -o $@

# Phony targets
.PHONY : clean test
test : $(TESTING)
	./$(TESTING) $(PARAMETERS)
clean :
	@-rm -rf bin/* $(EXECUTABLES_UNFILTERED) > /dev/null
