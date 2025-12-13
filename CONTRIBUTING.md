# CONTRIBUTING

このリポジトリでは Bazel の Bzlmod を前提としています。`WORKSPACE` は利用せず、`MODULE.bazel` で依存関係を管理してください。

- ZetaSQL のソースは `vendor/zetasql` に配置し、`MODULE.bazel` で `local_repository` を登録して `@zetasql//...` として参照します。
- 新しい依存追加や設定変更も `MODULE.bazel` で行い、`WORKSPACE` に戻す形にはしないでください。
- 変更を加える際は、本ファイルを参照し、既存の Bzlmod ベースの構成を保つようお願いします。
- サブモジュールは `.gitmodules` で HTTPS 指定になっています。権限まわりで PR が詰まらないよう、更新時は `git submodule sync --recursive && git submodule update --init --recursive` を実行して、URL や内容を揃えてください。
