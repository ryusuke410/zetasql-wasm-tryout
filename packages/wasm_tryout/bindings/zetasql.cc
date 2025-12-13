#include <emscripten/bind.h>
#include <emscripten/val.h>
#include "zetasql/parser/parser.h"

namespace {

// 結果とステータスを含む戻り値用の構造体
struct ParseResult {
  std::shared_ptr<zetasql::ParserOutput> output;
  bool success;
  std::string error_message;
};

} // namespace

// TODO: val を使いつつ型定義をするのがよさそう
// val を使わず xxx_values もあり。
// とにかく C++ のクラスを公開しない方針とする?
// → それは限界がありそう。
// 「今回はビルドができることまでをスコープとする。」
// C++ 側で print するコードを書いて、JS には bool しか返さないものとする

// C++ で専用ライブラリを実装した後に、
// どうやれば便利なバインディングになるかを考える。
// 単に delete を自動でしてくれるラッパーを作るだけでも十分かもしれない。

// EMSCRIPTEN_BINDINGS
EMSCRIPTEN_BINDINGS(zetasql_module) {
  // ParserOptionsのバインド
  // "zetasql::ParserOptions"と指定することで、JavaScriptからは"zetasql.ParserOptions"としてアクセス可能
  emscripten::class_<zetasql::ParserOptions>("zetasql::ParserOptions")
    .constructor<>()
    // 必要なメンバ変数やメソッドをここに追加
    ;

  // ParserOutputのバインド（smart_ptrを使用）
  emscripten::class_<zetasql::ParserOutput>("zetasql::ParserOutput")
    .smart_ptr<std::shared_ptr<zetasql::ParserOutput>>("shared_ptr<zetasql::ParserOutput>")
    // ParserOutputのメソッドなどをここに追加
    ;

  // 結果構造体のバインド
  emscripten::value_object<ParseResult>("ParseResult")
    .field("output", &ParseResult::output)
    .field("success", &ParseResult::success)
    .field("errorMessage", &ParseResult::error_message)
    ;

  // 匿名関数を使って直接バインド
  emscripten::function("parseStatement",
    [](const std::string& statement_string, const zetasql::ParserOptions& parser_options_in) -> ParseResult {
      ParseResult result;
      std::unique_ptr<zetasql::ParserOutput> output;

      absl::Status status = zetasql::ParseStatement(statement_string, parser_options_in, &output);

      result.success = status.ok();
      if (status.ok()) {
        result.output = std::shared_ptr<zetasql::ParserOutput>(std::move(output));
      } else {
        result.error_message = status.ToString();
      }

      return result;
  });
}
