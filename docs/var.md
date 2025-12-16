# var — 基本型とユーティリティ

## 概要
このモジュールは基本的な型エイリアスと文字列型（`StrSlice` / `String`）のインターフェースを提供します。

## 所在
- ヘッダファイル: `include/m_var.h`
- 実装ファイル: `src/m_var.c`

## 提供される型・マクロ・関数一覧
- `i8,i16,i32,i64,u8,u16,u32,u64` — 固定幅整数型の別名
- `isize, usize` — ポインタサイズに合わせた符号付き/符号無し整数
- `f32,f64` — 浮動小数点型
- `boolean`, `true`, `false` — ブール型
- `StrSlice` — 読み取り専用の文字列スライス
- `String` — 所有する可変文字列
- `str_lit(lit)` — リテラルから `StrSlice` を作るマクロ

### 関数（実装側）
- `StrSlice str_slice(const char *s, usize len);`
- `boolean str_eq(StrSlice a, StrSlice b);`
- `StrSlice str_sub(StrSlice s, usize pos, usize len);`
- `String string_new(void);`
- `void string_free(String *s);`
- `String string_from_slice(StrSlice src);`
- `Status string_push(String* s, char c);`
- `Status string_append(String* s, StrSlice tail);`
- `StrSlice string_as_slice(const String* s);`

## 詳細（API）
- `StrSlice str_slice(const char *s, usize len)`
  - 説明: 生の C 文字列と長さから `StrSlice` を作成する（借用、ヌル終端は保証されない）

- `String string_new(void)`
  - 説明: 空の `String` を作成する。呼び出し元は `string_free` で解放すること。
  - エラー: 実装によりメモリ割当てで `Status_Nomem` を返す場合がある。

- `Status string_append(String* s, StrSlice tail)`
  - 説明: `tail` の内容を `s` に追加する。必要に応じて容量を増やす。
  - 戻り値: `Status`（`Status_Ok` 成功、`Status_Nomem` 失敗）

## 使用例
```c
String s = string_new();
string_append(&s, str_lit("hello"));
string_push(&s, '!');
StrSlice slice = string_as_slice(&s);
printf("%.*s\n", (int)slice.len, slice.data);
string_free(&s);
```

## 注意点
- `String` は所有権を持つため、関数に渡す場合所有権移動や参照のルールに注意する。
- `str_lit` はリテラルに対してのみ使う。

## 互換性 / 要件
- GNU 拡張（statement expressions, __auto_type）を使用しているため、GCC/Clang を想定しています。

## 関連
- `docs/vec.md`, `docs/result.md`
