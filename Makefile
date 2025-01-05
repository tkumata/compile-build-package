# コンパイラ
CC = cc

# コンパイルオプション
CFLAGS = -Wall -Wextra -O2

# 実行ファイル名
TARGET = 02helloworld

# ソースファイル
SRCS = 02helloworld.c 02hello.c

# オブジェクトファイル
OBJS = $(SRCS:.c=.o)

# インストール先（デフォルト）
PREFIX = /usr/local

# ビルドルール
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンアップ
clean:
	rm -f $(OBJS) $(TARGET)

# 再構築
rebuild: clean all

# インストール
install: $(TARGET)
	install -d $(PREFIX)/bin
	install $(TARGET) $(PREFIX)/bin

# アンインストール
uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)

.PHONY: all clean rebuild install uninstall
