

SRC_DIR = src

INC_DIR = inc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
CC = clang

LIBSDIR = libs

LIBS = -L$(LIBSDIR)/json-c/libjson-c.a -llibjson-c -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lpthread -lz -lm -ldl -lpthread -lz -lm -ldl -lcrypt

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic 

RM = rm -rf

all: $(NAME) clean uchat_server

$(NAME):  uchat_server

#client:
#	@clang -o client clientSource/*.c -I $(INC_DIR)
#	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

uchat_server:
	@clang -o uchat_server -L$${HOME}/.brew/lib/ -I$${HOME}/.brew/include/ $(CFLAGS) -I$(INC_DIR) -lmysqlclient -ljson-c src/*.c
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

clean:
	@$(RM) $(OBJ_DIR)
#	@printf "$(OBJ_DIR) in $(NAME)\t \033[31;1mdeleted\033[0m\n"

uninstall: clean
#	@$(RM) client
	@$(RM) uchat_server
	@@printf "server\t \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall