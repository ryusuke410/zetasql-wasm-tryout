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
git submodule update --init --recursive && cp ./zetasql/.gitignore.txt .git/modules/vendor/zetasql/info/exclude && (cd vendor/zetasql && bazelisk build --copt='-mmacosx-version-min=10.13' -c opt --dynamic_mode=off ...)
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

※ 10 GB ぐらいのサイズになるので、今は一部だけを zip しています。（今後実需に応じてワークフローを修正するなどする予定です。）

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

## Node.js の setup

`.nvmrc` を参考に指定バージョンの Node.js を利用可能な状態にしてください。

## emscripten と wasm の tryout

以下のコマンドで動作確認ができます。

```sh
npm run emscripten-tryout:build-and-demo
```

## wip bazel + emscripten + wasm の tryout

TODO: `vendor/zetasql/zetasql/public/BUILD` を確認して、 zetasql での Bazel の書き方に慣れる。

## wip zetasql tools wasm_tryout

こちらで開発した tools を以下に挿入してみています。
（本当は外部に作れるので修正します。 TODO: `vendor/zetasql/zetasql/public/BUILD` を確認する。）

```sh
cp ./zetasql/.gitignore.txt .git/modules/vendor/zetasql/info/exclude && ln -sf './../../../../zetasql/wasm_tryout' ./vendor/zetasql/zetasql/tools/wasm_tryout
```

## ロードマップ

- [x] zetasql 自体のビルドができることを確認する
- [x] emscripten と wasm を使った C++ ライブラリの ECMA Script バインディングを試す
- [ ] bazel での ECMA Script バインディングのビルドを試す
- [ ] wasm を使った zetasql の ECMA bindings を作り、例として 1 つの API のみ bindings を実装する
- [ ] C++ 実装で、parser と unparser を macos と ubuntu で使えるようにする
- [ ] C++ 実装で、 BigQuery のクエリの静的な型チェッカーを macos と ubuntu で使えるようにする
- [ ] wasm を使った zetasql の ECMA bindings を作り、以上のツールを TypeScript で再実装する（ツールの実装に必要な bindings しか実装しない。）
- [ ] zetasql-npm や go-zetasql のインタフェースを理解する
- [ ] Node.js bindings を全てのインタフェースに拡張する

## ポエム

正しい bazel への引数を見付けるまで、以下のバグに悩まされた。
このタスクに着手する 4 日前に bug fix が入っていたのでよき思い出。

<https://github.com/abseil/abseil-cpp/issues/1840>
