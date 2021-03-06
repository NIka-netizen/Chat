CC = clang
LIB = libmx.a
NAME = uchat
LIBSDIR = libs

base = main authorization_screen chat_screen registration_screen css\

connection = data_to_str \

dirs = base connection \


FILES = $(foreach dir, $(dirs), $($(dir):%=$(dir)/%))

LIBS = -L$(LIBSDIR)/json-c/libjson-c.a -llibjson-c -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -ldl -lpthread -lz -lm -ldl -lcrypt

SRC_DIR = src/
OBJ_DIR = obj/
LIB_DIR = ../libmx/

SRC = $(FILES:%=$(SRC_DIR)%.c)
OBJ = $(FILES:%=$(OBJ_DIR)%.o)
LIB_PATH = $(LIB_DIR)$(LIB)

WFLAGS = -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument \
	-Wno-unused-variable -Wno-unused-function -Wno-unused-parameter

LFLAGS = -Iinc -I$(LIB_DIR)inc -I/usr/local/opt/openssl/include \
	-L/usr/local/opt/openssl/lib -lssl -lcrypto -L. \
	-L$${HOME}/.brew/lib/ -I$${HOME}/.brew/include/ -I$(INC_DIR) -lmysqlclient -ljson-c ` pkg-config --cflags --libs gmodule-2.0`

#CFLAGS = -Ofast -march=native -flto -rdynamic

PKGCONFIG = `pkg-config --libs --cflags gtk+-3.0`
PGKCONFIGFLAGS = `pkg-config --cflags gtk+-3.0`

COMPILE = $(CC) -std=c11 -pipe $(WFLAGS) $(LFLAGS)
EXEC_IT = make -sf Makefile
EXEC_LD = $(EXEC_IT) -C $(LIB_DIR)
PRINT = printf
MKDIR = mkdir -p
RM = /bin/rm -rf
TARGET = release

R = \033[1;91m
G = \033[1;92m
Y = \033[1;93m
B = \033[1;94m
M = \033[1;95m
C = \033[1;96m
S = \033[38;5;45;1m
D = \033[0m
F = \033[5m
A = \033[A
K = \033[K

all: $(LIB) $(NAME)

$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(dirs), $@/$(dir))

$(LIB):
	@$(EXEC_LD)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(PRINT) "$K$G COMPILING $Y[$M$(TARGET)$Y] $B$(<:$(SRC_DIR)%=%)$D\r"
	@$(COMPILE)  $(PGKCONFIGFLAGS) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(PRINT) "$K$G COMPILING $Y[$M$(TARGET)$Y] $R$(NAME)$D\r"
	@$(COMPILE)  $(PKGCONFIG) $(LIB_PATH) $(OBJ) -o $(NAME)
	@$(PRINT) "$K"

clean:
	@$(EXEC_LD) $@
	@$(RM) $(OBJ_DIR)

uninstall:
	@$(EXEC_LD) $@
	@$(RM) $(OBJ_DIR) $(NAME)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
