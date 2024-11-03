# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

# folder structure
SRC_DIR = src
BIN_DIR = bin
LIB_DIR = lib

# target executable
TARGET = $(BIN_DIR)/mps
TARGET_DBG = $(BIN_DIR)/mps_dbg

# source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) 

# default target is optimized version
all: $(TARGET)

# optimized version compile
$(TARGET):
	@mkdir -p $(BIN_DIR)
	$(CC) $(OPTFLAGS) $(SRCS) -o $(TARGET)

# debugging version compile
debug: $(TARGET_DBG)

$(TARGET_DBG):
	@mkdir -p $(BIN_DIR)
	$(CC) $(DBGFLAGS) $(SRCS) -o $(TARGET_DBG)

# clean command
clean:
	rm -rf $(BIN_DIR)/*