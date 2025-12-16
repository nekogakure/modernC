# panic — 致命的エラー報告

## 概要
`panic` は回復不能なエラーを報告してプログラムを終了させるユーティリティです。デバッグ時や `unwrap` 系での失敗時に使用されます。

## 所在
- ヘッダファイル: `include/m_result.h`（宣言）
- 実装ファイル: `src/m_result.c`（実装）

## 提供される関数
- `noreturn void panic(const char *msg);`

## 詳細
- `panic` はメッセージを標準エラーに出力し、プロセスを終了させる（実装依存）。
- `unwrap` / `unwrap_option` マクロは失敗時に `panic` を呼び出す。

## 使用例
```c
if (ptr == NULL) panic("unexpected null");
```

## 注意点
- ランタイムを即終了させるため、ライブラリの公開 API で `panic` を安易に呼ぶべきではない（アプリケーション内部のデバッグヘルパーとして使う）。

## 互換性
- なし（標準 C）。

## 関連
- `docs/result.md`, `docs/option.md`
