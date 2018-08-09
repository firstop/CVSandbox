# Executable application build steps valid for MS Windows + MinGW environment

SELF_DIR := $(dir $(lastword $(MAKEFILE_LIST)))

# compiler options
ifneq "$(findstring debug, $(MAKECMDGOALS))" ""
# "Debug" build - no optimization, and debugging symbols 
OUT_FOLDER = "$(SELF_DIR)..\..\..\..\build\$(TARGET)\debug\bin\"
else 
# "Release" build - optimization, and no debug symbols 
OUT_FOLDER = "$(SELF_DIR)..\..\..\..\build\$(TARGET)\release\bin\"
endif 

CFLAGS += $(INCLUDES)
LDFLAGS += $(LIBDIR) $(LIBS)

all: build post_build

debug: build post_build
 
%.o: $(SRC_FILE_EXT)
	$(COMPILER) $(CFLAGS) -c $^ -o $@

$(OUT): $(OBJ)
	$(COMPILER) -o $@ $(OBJ) $(LDFLAGS)

build: $(OUT)
	xcopy /Y $(OUT) $(OUT_FOLDER)

post_build: $(OUT)

clean:
	del $(OBJ) $(OUT)