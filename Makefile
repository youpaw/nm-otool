INC_DIRS		:= ./share
NM_INC_DIRS		:= ./nm
OTOOL_INC_DIRS	:= ./otool

PRINTF_DIR		:= ./printf
PRINTF_INC_DIRS	:= src

LIBFT_DIR		:= $(PRINTF_DIR)/libft
LIBFT_INC_DIRS	:= env avl char file graph hash_map list math memory num \
					string vector arr optparse regex error .
INC_FLAGS		:= $(addprefix -I ,$(INC_DIRS)) \
					$(addprefix -I , \
						$(addprefix $(LIBFT_DIR)/,$(LIBFT_INC_DIRS))) \
					$(addprefix -I , \
                    	$(addprefix $(PRINTF_DIR)/,$(PRINTF_INC_DIRS)))
NM_INC_FLAGS	:= $(addprefix -I ,$(INC_DIRS)) \
					$(addprefix -I ,$(NM_INC_DIRS)) \
					$(addprefix -I , \
						$(addprefix $(LIBFT_DIR)/,$(LIBFT_INC_DIRS))) \
					$(addprefix -I , \
						$(addprefix $(PRINTF_DIR)/,$(PRINTF_INC_DIRS)))
OTOOL_INC_FLAGS	:= $(addprefix -I ,$(INC_DIRS)) \
					$(addprefix -I ,$(OTOOL_INC_DIRS)) \
					$(addprefix -I , \
						$(addprefix $(LIBFT_DIR)/,$(LIBFT_INC_DIRS))) \
					$(addprefix -I , \
						$(addprefix $(PRINTF_DIR)/,$(PRINTF_INC_DIRS)))

SRC_DIR			:= ./src
SRCS			:= share/del_binary_info.c						\
					share/fat/get_header_fat.c					\
					share/fat/parse_header_fat.c				\
					share/fat/parse_header_fat_32.c				\
					share/fat/parse_header_fat_64.c				\
					share/get_binary_info.c						\
					share/get_segments.c						\
					share/mach-o/get_header_mach_o_32.c			\
					share/mach-o/get_header_mach_o_64.c			\
					share/mach-o/get_load_cmd_mach_o.c			\
					share/mach-o/get_sections_mach_o_32.c		\
					share/mach-o/get_sections_mach_o_64.c		\
					share/mach-o/get_segments_mach_o_32.c		\
					share/mach-o/get_segments_mach_o_64.c		\
					share/parse_magic.c							\
					share/print_hexdump.c						\
					share/print_nt_error.c


NM_SRCS			:= nm/cmp_sym_info.c							\
					nm/get_symbol_char.c						\
					nm/get_symtab_cmd.c							\
					nm/mach-o/get_nlists_mach_o_32.c			\
					nm/mach-o/get_nlists_mach_o_64.c			\
					nm/mach-o/get_sym_info_table_mach_o_32.c	\
					nm/mach-o/get_sym_info_table_mach_o_64.c	\
					nm/mach-o/get_symtab_mach_o_32.c			\
					nm/mach-o/get_symtab_mach_o_64.c			\
					nm/nm.c										\
					nm/print_symtab.c

OTOOL_SRCS		:= otool/mach-o/get_sections_data_mach_o_32.c	\
					otool/mach-o/get_sections_data_mach_o_64.c	\
					otool/otool.c								\
					otool/print_sects.c

OBJ_DIR			:= ./obj
OBJS			:= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
NM_OBJS			:= $(addprefix $(OBJ_DIR)/,$(NM_SRCS:.c=.o))
OTOOL_OBJS		:= $(addprefix $(OBJ_DIR)/,$(OTOOL_SRCS:.c=.o))

DEPS    		:= $(OBJS:.o=.d)
NM_DEPS			:= $(NM_OBJS:.o=.d)
OTOOL_DEPS		:= $(OTOOL_OBJS:.o=.d)

PRINTF			:= $(PRINTF_DIR)/libftprintf.a
CFLAGS			:= -MMD -Wall -Wextra -Werror
LFLAGS			:= -L $(PRINTF_DIR) -l ftprintf

NAME			:= ft_nm_otool
NM_NAME			:= ft_nm
OTOOL_NAME		:= ft_otool

.PHONY: all lib clean fclean re

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/nm/mach-o
	mkdir -p $(OBJ_DIR)/otool/mach-o
	mkdir -p $(OBJ_DIR)/share/fat
	mkdir -p $(OBJ_DIR)/share/mach-o

$(OBJ_DIR)/%.o: %.c
	gcc $(CFLAGS) $(INC_FLAGS) -o $@ -c $<

-include $(DEPS)
-include $(NM_DEPS)
-include $(OTOOL_DEPS)

$(NM_NAME): $(NM_OBJS)
	gcc -o $(NM_NAME) $(OBJS) $(NM_OBJS) $(LFLAGS)

$(OTOOL_NAME): $(OTOOL_OBJS)
	gcc -o $(OTOOL_NAME) $(OBJS) $(OTOOL_OBJS) $(LFLAGS)

$(NAME): $(OBJ_DIR) $(OBJS) $(NM_NAME) $(OTOOL_NAME) | lib

lib:
	make -C $(PRINTF_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(PRINTF_DIR)
fclean: clean
	rm -f $(NM_NAME) $(OTOOL_NAME)
	make fclean -C $(PRINTF_DIR)

re: fclean all
