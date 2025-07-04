##
## EPITECH PROJECT, 2025
## day01
## File description:
## Makefile
##

ECHO = /bin/echo -e
DEFAULT = "\033[00m"
BOLD = "\e[1m"
RED = "\e[31m"
GREEN = "\e[32m"
LIGHT_BLUE = "\e[94m"
WHITE = "\e[1;37m"

RM = rm -f

SRC		=	src/main.cpp \
			src/Profil.cpp \
			src/Core.cpp \
			src/WindowsSerialBackend.cpp \
			src/LinuxSerialBackend.cpp \
			src/Config.cpp \
			src/UI/Ui.cpp \
			src/UI/components/AButton.cpp \
			src/UI/components/NewConfigButton.cpp \
			src/UI/ButtonFactory.cpp \
			src/UI/components/DefaultButton.cpp \
			src/UI/components/TextBox.cpp \
			src/UI/components/LoadConfigButton.cpp \
			src/UI/components/ExitButton.cpp \
			src/UI/components/ActionButton.cpp \
			src/UI/components/ShowConfigButton.cpp \
			src/UI/components/StartButton.cpp \
			src/UI/components/StopButton.cpp \

NAME	=	hub_ir

GHC 	= 	g++

FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

PWD = $(shell pwd)

all:
	@$(GHC) $(SRC) -o $(NAME) -g $(FLAGS)\
	&& $(ECHO) $(BOLD) $(GREEN)"\n► BUILD SUCCESS !"$(DEFAULT) \
	|| ($(ECHO) $(BOLD) $(RED)"\n► BUILD FAILED"$(DEFAULT) && exit 1)

clean:
	@$(RM) *hi
	@$(RM) *o
	@$(RM) *~
	@$(RM) *#
	@($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" CLEAN "$(DEFAULT))

fclean:	clean
	@$(RM) $(NAME)
	@$(RM) *.gcda
	@$(RM) *.gcno
	@$(RM) vgcore.*
	@($(ECHO) $(BOLD) $(GREEN)✓$(LIGHT_BLUE)" FCLEAN "$(DEFAULT))

build:
	docker build -t hub_ir_win .

ex:
	docker run --rm -v "$(PWD)/out:/out" hub_ir_win cp /app/hub_ir.exe /out/


re: fclean all
