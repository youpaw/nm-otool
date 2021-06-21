SHARE_INC_DIRS	:= ./share
NM_INC_DIRS		:= ./nm
OTOOL_INC_DIRS	:= ./otool

PRINTF_DIR		:= ./printf
PRINTF_INC_DIRS	:= src

LIBFT_DIR		:= $(PRINTF_DIR)/libft
LIBFT_INC_DIRS	:= env avl char file graph hash_map list math memory num \
					string vector arr optparse regex error .

FTPRINTF_INC_FLAGS := $(addprefix -I , \
							$(addprefix $(LIBFT_DIR)/,$(LIBFT_INC_DIRS))) \
						$(addprefix -I , \
							$(addprefix $(PRINTF_DIR)/,$(PRINTF_INC_DIRS)))

SHARE_INC_FLAGS	:= $(addprefix -I ,$(SHARE_INC_DIRS)) $(FTPRINTF_INC_FLAGS)
NM_INC_FLAGS	:= $(SHARE_INC_FLAGS) $(FTPRINTF_INC_FLAGS) \
					$(addprefix -I ,$(NM_INC_DIRS))
OTOOL_INC_FLAGS	:= $(SHARE_INC_FLAGS) $(FTPRINTF_INC_FLAGS) \
					$(addprefix -I ,$(OTOOL_INC_DIRS))


SHARE_SRC_DIR	:= ./share
SHARE_SRCS		:= del_binary_info.c				\
					fat/get_header_fat.c			\
					fat/parse_header_fat.c			\
					fat/parse_header_fat_32.c		\
					fat/parse_header_fat_64.c		\
					get_binary_info.c				\
					get_segments.c					\
					mach-o/get_header_mach_o_32.c	\
					mach-o/get_header_mach_o_64.c	\
					mach-o/get_load_cmd_mach_o.c	\
					mach-o/get_sections_mach_o_32.c	\
					mach-o/get_sections_mach_o_64.c	\
					mach-o/get_segments_mach_o_32.c	\
					mach-o/get_segments_mach_o_64.c	\
					parse_magic.c					\
					print_hexdump.c					\
					print_nt_error.c

NM_SRC_DIR	:= ./nm
NM_SRCS			:= cmp_sym_info.c							\
					get_symbol_char.c						\
					get_symtab_cmd.c						\
					mach-o/get_nlists_mach_o_32.c			\
					mach-o/get_nlists_mach_o_64.c			\
					mach-o/get_sym_info_table_mach_o_32.c	\
					mach-o/get_sym_info_table_mach_o_64.c	\
					mach-o/get_symtab_mach_o_32.c			\
					mach-o/get_symtab_mach_o_64.c			\
					nm.c									\
					print_symtab.c

OTOOL_SRC_DIR	:= ./otool
OTOOL_SRCS		:= mach-o/get_sections_data_mach_o_32.c		\
					mach-o/get_sections_data_mach_o_64.c	\
					otool.c									\
					print_sects.c

OBJ_DIR			:= ./obj

SHARE_OBJ_DIR	:= $(OBJ_DIR)/share
SHARE_OBJS		:= $(addprefix $(SHARE_OBJ_DIR)/,$(SHARE_SRCS:.c=.o))

NM_OBJ_DIR		:= $(OBJ_DIR)/nm
NM_OBJS			:= $(addprefix $(NM_OBJ_DIR)/,$(NM_SRCS:.c=.o))

OTOOL_OBJ_DIR	:= $(OBJ_DIR)/otool
OTOOL_OBJS		:= $(addprefix $(OTOOL_OBJ_DIR)/,$(OTOOL_SRCS:.c=.o))

SHARE_DEPS		:= $(SHARE_OBJS:.o=.d)
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

$(SHARE_OBJ_DIR):
	mkdir -p $(OBJ_DIR)/share/fat
	mkdir -p $(OBJ_DIR)/share/mach-o

$(NM_OBJ_DIR):
	mkdir -p $(OBJ_DIR)/nm/mach-o

$(OTOOL_OBJ_DIR):
	mkdir -p $(OBJ_DIR)/otool/mach-o

$(SHARE_OBJ_DIR)/%.o: $(SHARE_SRC_DIR)/%.c
	gcc $(CFLAGS) $(SHARE_INC_FLAGS) -o $@ -c $<
-include $(SHARE_DEPS)

$(NM_OBJ_DIR)/%.o: $(NM_SRC_DIR)/%.c
	gcc $(CFLAGS) $(SHARE_INC_FLAGS) $(NM_INC_FLAGS) -o $@ -c $<
-include $(NM_DEPS)

$(OTOOL_OBJ_DIR)/%.o: $(OTOOL_SRC_DIR)/%.c
	gcc $(CFLAGS) $(SHARE_INC_FLAGS) $(OTOOL_INC_FLAGS) -o $@ -c $<
-include $(OTOOL_DEPS)

$(NM_NAME): $(SHARE_OBJ_DIR) $(SHARE_OBJS) $(NM_OBJ_DIR) $(NM_OBJS) | lib
	gcc -o $(NM_NAME) $(SHARE_OBJS) $(NM_OBJS) $(LFLAGS)

$(OTOOL_NAME): $(SHARE_OBJ_DIR) $(SHARE_OBJS) $(OTOOL_OBJ_DIR) $(OTOOL_OBJS) | lib
	gcc -o $(OTOOL_NAME) $(SHARE_OBJS) $(OTOOL_OBJS) $(LFLAGS)

$(NAME): $(NM_NAME) $(OTOOL_NAME)

lib:
	make -C $(PRINTF_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(PRINTF_DIR)
fclean: clean
	rm -f $(NM_NAME) $(OTOOL_NAME)
	make fclean -C $(PRINTF_DIR)

re: fclean all
