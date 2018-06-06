CC := g++ --std=c++11
IFLAGS := $(foreach d, \
	  $(shell find . -type f -name "*.h*" -printf '%h\n' | sort -u), \
	  -I$(d))

EXECUTABLES := $(foreach e, \
	       $(shell ls -d src/*), \
	       $(shell basename $(e)))
COMMON_OBJ := $(foreach o, \
	      $(shell find lib -name "*.cpp"), \
	      $(o:lib/%.cpp=bin/lib/%.o))

define build_executable =
$(eval $(1)_OBJ = $(foreach o, \
		  $(shell find src/$(1)/ -name "*.cpp"), \
		  $(o:%.cpp=bin/%.o)))
$(1) : $(COMMON_OBJ) $($(1)_OBJ)
	$(CC) -o $(1) $($(1)_OBJ) $(COMMON_OBJ)
endef

$(foreach e, $(EXECUTABLES), $(eval $(call build_executable,$e)))

.SECONDEXPANSION:
bin/%.o : %.cpp $$(wildcard $$*.h)
	@if [ ! -d "$(@:%/$(shell basename $@)=%)" ]; \
	then \
		mkdir -p $(@:%/$(shell basename $@)=%); \
	fi;
	$(CC) -c $< $(IFLAGS) -o $@

.PHONY : clean test

clean :
	@-rm -r bin/* > /dev/null

test :
	./simulate res/map.svg test
