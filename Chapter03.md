# パッケージについて

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
