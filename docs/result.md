# result — Result 型とエラーハンドリング

## 概要
`Result` 系は、関数が成功または失敗を返す際に使う小さなユーティリティです。エラー伝播を明示的かつ簡潔に表現できます。

## 所在
- ヘッダファイル: `include/m_result.h`
- 実装ファイル: `src/m_result.c`

## 提供される型・マクロ・関数一覧
- `Result` — 成否のみを持つ型（.status）
- `ResultOf(T)` — 成功時に `T` 値を持つ結果型
- `Ok()`, `Err(code)`, `OkVal(v)`, `ErrVal(e)` — コンストラクタマクロ
- `IsOk(r)`, `IsErr(r)` — 判定
- `Try(r)` — Result を返す関数内でエラーを呼び出し元へ伝播する
- `TryVal(r)` — 値を返す ResultOf(T) から値を取り出し、エラーなら伝播する
- `unwrap`, `unwrap_or` — ResultOf(String) 向けのアンラップマクロ
- `panic(const char *msg)` — 致命的エラー出力（noreturn）
- `ResultString f(String s);` — 例示的な関数（実装あり）

## 詳細（API）
- `Result` は `.status` を持つ単純な構造。`Status_Ok`(0) で成功。
- `Try(r)` は内部で `_r = (r)` を評価し失敗時に `return _r;` を行う（つまり呼び出し元が Result を返すことを前提とする）。
- `TryVal(r)` は成功時にその `.value` を返す式として使える。

## 使用例
```c
Result do_work(void) {
    Result r = some_helper();
    Try(r); // some_helper が Err ならここで return Err(...)
    return Ok();
}

ResultOf(int) compute(void) {
    if (bad) return ErrVal(Status_Invalid);
    return OkVal(123);
}

Result use_compute(void) {
    int v = TryVal(compute());
    printf("value=%d\n", v);
    return Ok();
}
```

## 注意点
- `Try` / `TryVal` はマクロであり、式を一度だけ評価するように内部で工夫しているが、引数に副作用を持つ式を渡す際は注意。

## 互換性 / 要件
- GNU 拡張（statement expressions）を使用しているため、GCC/Clang での利用を想定しています。

## 関連
- `docs/option.md`, `docs/var.md`
