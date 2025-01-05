# コンパイルとビルドについて

前述のとおり、プログラムを動かせる形にするには、次の 2 つのステップがあります。

1. コンパイル  
   ソースコード (人間が書いたプログラム) をコンピュータが理解できる形 (機械語) に変換する作業のことです。たとえば、以下のようなコマンドで行います。

   ```shell
   cc -c 02helloworld.c -o 02helloworld.o  # コンパイル
   cc -c 02hello.c -o 02hello.o            # コンパイル
   ```

2. ビルド  
   コンパイルしたファイルをつなぎ合わせて、ひとつの実行可能なファイル（プログラム）を作る作業を指します。以下のようにリンクを行います。

   ```shell
   cc 02helloworld.o 02hello.o -o 02helloworld  # リンク
   ```

これら一連の流れをまとめて「ビルド」と呼びます。

## 自動化で便利に: Makefile の利用

手作業でコンパイルやリンクするのは面倒かつミスの可能性が増えます。そこで「Makefile」という仕組みを使って自動化します。以下は簡単な Makefile ファイルの例です。

```Makefile
# コンパイラ
CC = cc

# コンパイルオプション
# -Wall: プログラムに潜むバグや非推奨の書き方を見つけやすくするため、多くの警告メッセージを出力するようにします。
# -Wextra: -Wall よりもさらに厳しいチェックを追加します。これにより、より細かい問題も検出される可能性があります。
# -O2: コンパイラが生成するコードを速く、またはサイズを小さくするための最適化を行います。-O2 は、ほとんどの一般的な最適化を行いながら、コンパイル時間やデバッグのしやすさに大きな影響を与えないバランスの良い設定です。
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
```

### 使い方

- make を実行するとビルドが行われます。
- make clean で中間ファイルや実行ファイルを削除します。
- make rebuild で最初からビルドし直します。

**注意**: コピペする場合、インデント部分はスペースではなく「タブ文字」にしてください。

## 実行ファイルをインストールする

ビルドが終わると、プログラム (実行ファイル) が完成します。たとえば、02helloworld ができたとします。このファイルをコンピュータの特定の場所 (例: /usr/bin) に配置すると、UNIX 内で PATH を切っていれば、どこからでも実行できるようになります。これを「インストール」といいます。

例:
PHP の場合、以下のように実行ファイルや設定ファイルが配置されます。

- 実行ファイル: /usr/bin/php
- 設定ファイル: /etc/php.ini
- ライブラリ: /usr/lib/php/

ビルドは「料理を作る」作業、インストールは「料理をテーブルに並べる」作業と考えると分かりやすいです。

## パッケージとは？

複数の成果物 (実行ファイルや設定ファイル、ライブラリなど) をまとめて、簡単にインストール・管理できる形にしたものを「パッケージ」と呼びます。パッケージは次のように形式ごとに呼び名が違います。

| OS               | Format  | Name        | Command           |
| ---------------- | ------- | ----------- | ----------------- |
| Linux (Red Hat)  | .rpm    | RPM package | `rpm` `dnf` `yum` |
| Linux (Debian)   | .deb    | DEB package | `dpkg` `apt`      |
| macOS (Homebrew) | .tar.gz | bottole     | `brew`            |
| FreeBSD (Ports)  | .tar.gz | package     | `pkg`             |
| Windows          | unknown | unknown     | `winget`          |

プログラミング言語ごとにも専用のパッケージ管理ツールがあります。たとえば:

| Lang    | Command                  |
| ------- | ------------------------ |
| PHP     | `composer` `pear` `pecl` |
| Node.js | `npm` `yarn`             |
| Python  | `pip`                    |
| Go      | `go install` `go mod`    |
| Rust    | `cargo`                  |

これらを使うと、ライブラリやツールのインストールがとても簡単になります。

## パッケージ管理ツールの挙動

一部のパッケージ管理ツールは次のような挙動をします。

1. 必要なパッケージを探し、事前に用意された成果物 (バイナリなど) をインストールする。
2. 用意された成果物がない場合、ソースコードを取得してビルドを行い、システムにインストールする。

たとえば、以下のツールはこのような動きをします:

- Homebrew (brew)
- PHP 関連 (pear, pecl)

これにより、プログラムの導入が簡単で、柔軟に行える仕組みになっています。
