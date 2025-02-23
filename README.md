# zetasql wasm tryout

## ゴール

- parser と unparser を macos と ubuntu で使いたい
- BigQuery 用の analyzer を使いたい
- zeta sql を wasm で使いたい

## zetasql の macos 向けビルド

### zetasql の macos 向けビルドに必要なツール - bazel

適切なバージョンの bazelisk を準備してください。
例として `mise.toml` を参考されたい。
（mise を利用している場合は `mise trust` してください。）

### zetasql の macos 向けビルドに必要なツール - Xcode Command Line Tools

Xcode Command Line Tools が必要です。
ほとんどの場合は以下のコマンドでインストールできます。
コマンド実行すると、ポップアップがでてきてインストールできるか、
既にインストール済みというエラーがでるかのいずれかが典型的です。
（まれに上手く動かない場合がありますが、その場合は適宜調査してください。）

```sh
xcode-select --install
```

### zetasql の macos 向けビルドコマンド

以下のコマンドで全てのプロジェクトが問題なくビルドされるはずです。

```sh
git submodule update --init --recursive && cp zetasql/.gitignore.txt vendor/zetasql/.gitignore && (cd vendor/zetasql && bazelisk build --copt='-mmacosx-version-min=10.13' -c opt --dynamic_mode=off ...)
```

ビルドが完了すると、例えば `execute_query` のバイナリが使えるようになります。

```sh
file ./vendor/zetasql/bazel-bin/zetasql/tools/execute_query/execute_query
```

```sh
chmod u+x ./vendor/zetasql/bazel-bin/zetasql/tools/execute_query/execute_query && ./vendor/zetasql/bazel-bin/zetasql/tools/execute_query/execute_query --mode=parse,analyze,execute "SELECT 1 as one"
```

## zetasql の GitHub Actions でのビルド

`.github/workflows/build-zetasql.yml` がビルドのワークフローです。
`test/build-zetasql` ブランチに push するか、 workflow dispatch でビルドを実行します。

`bazel-bin` がアーティファクトとして入手可能です。

## zetasql の docker でのビルド

### zetasql の docker でのビルドコマンド

以下のコマンドで `linux/amd64` 向けにビルドができます。

```sh
git submodule update --init --recursive && (cd vendor/zetasql && docker build --platform=linux/amd64 -t zetasql-linux-amd64-mode-build .)
```

ビルドが完了すると、例えば `execute_query` のバイナリが使えるようになります。

```sh
docker run zetasql-mode-build --init -it --rm ls .
```

## bazel wasm の tryout

`s0l0ist/bazel-emscripten` が今も動くようなので、これを参考にしています。

以下のコマンドでデモ実行ができます。

```sh
git submodule update --init --recursive && (cd vendor/bazel-emscripten && npm install --frozen-lockfile && npm run build && npm run rollup && npm run demo)
```

## ロードマップ

- [ ] C++ 実装で、parser と unparser を macos と ubuntu で使えるようにする
- [ ] C++ 実装で、 BigQuery のクエリの静的な型チェッカーを macos と ubuntu で使えるようにする
- [ ] wasm を使った zetasql の Node.js binding を作り、以上のツールを TypeScript で再実装する（ツールの実装に必要な binding しか実装しない。）
- [ ] Node.js binding を全てのインタフェースに拡張する

## ポエム

正しい bazel への引数を見付けるまで、以下のバグに悩まされた。
このタスクに着手する 4 日前に bug fix が入っていたのでよき思い出。

<https://github.com/abseil/abseil-cpp/issues/1840>
