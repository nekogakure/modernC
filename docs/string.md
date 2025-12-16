# string — String / StrSlice

## 概要
`String` は所有する可変文字列、`StrSlice` は借用の読み取り専用スライスを表します。`String` は動的に拡張可能で、`string_append`/`string_push` などで操作します。

## 所在
- ヘッダファイル: `include/m_var.h`
- 実装ファイル: `src/m_var.c`

## 提供される型・マクロ・関数一覧
- `StrSlice` — { const char *data; usize len; }
- `String` — { char *data; usize len; usize cap; }
- `str_lit(lit)` — リテラルから `StrSlice` を作る
- `string_new()`, `string_free()`, `string_from_slice()`, `string_push()`, `string_append()`, `string_as_slice()`

## 詳細（API）
- `string_push(String* s, char c)` はバッファを必要に応じて拡張し、文字を追加する。失敗時は `Status_Nomem`。
- `string_append(String* s, StrSlice tail)` は `tail` を末尾に連結する。
- `string_as_slice` は `String` の内容を `StrSlice` として借用返却する。

## 使用例
```c
String s = string_new();
if (string_append(&s, str_lit("hello")) != Status_Ok) {
    panic("OOM");
}
string_push(&s, '\n');
StrSlice sl = string_as_slice(&s);
printf("%.*s", (int)sl.len, sl.data);
string_free(&s);
```

## 注意点
- `String` は内部でヌル終端を保持している（実装に依存）。
- 大きな文字列操作は再割当が多発するので注意。

## 互換性 / 要件
- `malloc`/`free` を使用。

## 関連
- `docs/var.md`
