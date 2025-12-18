# コンパイラ
CC = cc

# コンパイルオプション
CFLAGS = -Wall -Wextra -O2

# 実行ファイル名
TARGETS = 02helloworld 03webserver

# ビルドルール
all: $(TARGETS)

02helloworld: 02helloworld.o 02hello.o
	$(CC) $(CFLAGS) -o $@ $^

03webserver: 03webserver.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンアップ
clean:
	rm -f *.o $(TARGETS)

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
