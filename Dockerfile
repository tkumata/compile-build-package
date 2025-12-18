# --- ステージ1: ビルド環境 ---
FROM gcc:12 AS builder

WORKDIR /app

# ソースコードと Makefile をコンテナ内にコピー
COPY . .

# コンテナ内でビルドを実行
RUN make

# --- ステージ2: 実行環境 ---
FROM debian:bookworm-slim

WORKDIR /app

# ビルドステージで作った実行ファイルだけをコピー
COPY --from=builder /app/02helloworld .

# コンテナ起動時に実行するコマンド
CMD ["./02helloworld"]
