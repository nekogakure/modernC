# vec — Vec(T)（動的配列）

## 概要
`Vec(T)` はジェネリック風の動的配列マクロです。C のジェネリックがない中で、マクロを駆使して型安全に使えるように設計されています。

## 所在
- ヘッダファイル: `include/m_vec.h`
- 実装ファイル: `src/m_vec.c`

## 提供される型・マクロ・関数一覧
- `Vec(T)` — { T *data; usize len; usize cap; }
- `vec_new(T)` — 空の Vec を作成
- `vec_with_capacity(T, c)` — 指定容量で作成
- `vec_len(v)`, `vec_capacity(v)` — 情報取得
- `vec_push(v, item)` — 末尾に追加。内部で `vec_grow` を呼ぶことがある。
- `vec_pop(v)` — 末尾から取り出す。`Option(T)` を返す。
- `vec_free(v)` — バッファを解放
- `Result vec_grow(void** data, usize* cap, usize elem_size);`
- `Result vec_try_pop(void* data, usize* len, void* out, usize elem_size);`

## 詳細（API）
- `vec_push(v, item)` はマクロ。容量不足時は
  - `vec_grow` を呼んで容量を拡張する。失敗時は `Err` を返し、`vec_push` を呼んでいる関数から早期 return となる。
  - 成功時は `v.data[v.len++] = item;` を実行する。

- `vec_pop(v)` は `Option(T)` を返す。空の場合は `None`、それ以外は `Some(value)` を返す。

## 使用例
```c
Vec(int) v = vec_new(int);
for (int i = 0; i < 10; ++i) vec_push(v, i);
for (int i = 0; i < 10; ++i) {
    Option(int) o = vec_pop(v);
    if (is_some(o)) printf("popped: %d\n", o.value);
}
vec_free(v);
```

## 注意点 / トレードオフ
- `vec_push` はマクロであり、呼び出し元の関数が `Result` を返す型でない場合、そのままでは early-return の挙動が問題になる。
  - 対策: ラッパー関数を作る、あるいは `vec_try_push` のような関数を実装して `Result` を返す。
- メモリ拡張の戦略や再割当の挙動は実装による（倍増戦略など）。

## 互換性 / 要件
- `malloc` / `free` を使用するため標準 C ランタイムが必要。
- GNU 拡張を使用している。

## 関連
- `docs/var.md`, `docs/result.md`
