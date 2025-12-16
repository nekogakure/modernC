# option — Option 型（存在するかもしれない値）

## 概要
`Option(T)` は値が存在するかどうかを示す軽量な型です。値がある場合は `.is_some == true` で `.value` に保持されます。存在しない場合は `.is_some == false`。

## 所在
- ヘッダファイル: `include/m_option.h`
- 実装ファイル: `src/m_option.c`（未必須）

## 提供される型・マクロ・関数一覧
- `Option(T)` — { boolean is_some; T value; }
- `Some(v)` — 値を持つ Option を作る
- `None` — 値がない Option
- `is_some(o)`, `is_none(o)` — 判定
- `unwrap_option(o)` — 存在しない場合に `panic` する

## 詳細（API）
- `Option` は値をコピーして保持するため、大きな値を入れる場合は注意（ポインタを格納するか別設計を推奨）。
- `unwrap_option` は内部で `_o = (o); if (!_o.is_some) panic(...)` を行い、値がある場合に `_o.value` を返す。

## 使用例
```c
Option(int) find(int *arr, usize n, int key) {
    for (usize i = 0; i < n; ++i) {
        if (arr[i] == key) return Some((int)i);
    }
    return None;
}

Option(int) r = find(nums, cnt, 7);
if (is_some(r)) printf("found at index %d\n", r.value);
else printf("not found\n");
```

## 注意点
- `Some(v)` はコピー構文なのでムーブセマンティクスはない（C 標準の範囲）。

## 互換性 / 要件
- GNU 拡張（statement expressions）を使用している。

## 関連
- `docs/result.md`, `docs/var.md`
