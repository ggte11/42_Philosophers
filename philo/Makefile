NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -pthread
OBJ_DIR		= obj

SRCS		= philosophers.c initialize.c utils.c \
			  philo_actions.c monitoring.c
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
BLUE		= \033[0;34m
CYAN		= \033[0;36m
RESET		= \033[0m

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "$(CYAN)🔨 Compiling $(YELLOW)$<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(BLUE)🔗 Linking objects...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread
	@echo "$(GREEN)✅ $(NAME) created successfully!$(RESET)"

clean:
	@if [ -d $(OBJ_DIR) ]; then \
		echo "$(RED)🗑️  Removing object files...$(RESET)"; \
		rm -rf $(OBJ_DIR); \
		echo "$(GREEN)✨ Object files cleaned!$(RESET)"; \
	fi

fclean: clean
	@if [ -f $(NAME) ]; then \
		echo "$(RED)💥 Removing $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
		echo "$(GREEN)✨ $(NAME) removed!$(RESET)"; \
	fi

re: fclean all

.PHONY: all clean fclean re