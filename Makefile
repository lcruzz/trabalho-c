# ============================================
# Configurações do compilador
# ============================================
CC      = gcc
CFLAGS  = -Wall -Wextra -g -std=gnu11
INCLUDE = -I./include

# ============================================
# Diretórios
# ============================================
SRC_DIR   = src
BUILD_DIR = build

# ============================================
# Arquivos
# ============================================
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = biblioteca

# ============================================
# Alvo padrão
# ============================================
all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build concluído: $@"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# ============================================
# Alvos utilitários
# ============================================
run: all
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
	@echo "🧹 Arquivos removidos."

rebuild: clean all

info:
	@echo "Fontes : $(SRCS)"
	@echo "Objetos: $(OBJS)"
	@echo "Alvo   : $(TARGET)"

.PHONY: all run clean rebuild info