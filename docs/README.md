`modernC`は、C言語に近代的な機能を持ち込むライブラリです。 
バニラだと冗長なエラーハンドリングや文字列／配列処理を手早く書けるようにします。

設計方針：
- 小さく明快に。余計な依存は増やさない。
- マクロでジェネリックな振る舞いを提供し、実行時コストは最小限に。
- `Result`/`Option`などの明示的なエラー表現を奨励する。

### できること
- 成功／失敗を扱う`Result`でエラー伝播をシンプルに書ける。
- 値またはエラーを返す`ResultOf(T)`を使える。
- オプションの戻り値を`Option(T)`で表現できる。
- 所有する可変文字列`String`とスライス`StrSlice`を扱える。
- ジェネリック風`Vec(T)`（動的配列）を使って配列操作が簡単にできる。
- 小さな型エイリアス（i32, usize 等）とユーティリティを提供。
- `let`での変数宣言（C23でのみ有効）。
- `panic`で致命的エラーを報告。

### ドキュメント一覧
- [変数型と基本ユーティリティ](var.md)
- [Result型とエラーハンドリング](result.md)
- [Option型](option.md)
- [Vec(T)動的配列](vec.md)
- [StringとStrSlice](string.md)
- [panicによるエラー報告](panic.md)

### 提供される主要な型・マクロ
- 基本型エイリアス
  - i8,i16,i32,i64, u8,u16,u32,u64, isize, usize, f32, f64
  - `boolean` (`true`/`false`)、`StrSlice`（read-only slice）、`String`（owned mutable string）

- Result系
  - `Result`: 成否のみを持つ型（.status）
  - `ResultOf(T)`: 成功時にT値を持つResult
  - マクロ：`Ok()`, `Err(code)`, `OkVal(v)`, `ErrVal(e)`
  - 判定：`IsOk(r)`, `IsErr(r)`
  - エラープロパゲーション：`Try(r)`（Resultを返す関数内で早期return）、`TryVal(r)`（値を取り出す）
  - 例外的アンラップ：`unwrap` / `unwrap_or`

- Option
  - `Option(T)`: { boolean is_some; T value; }
  - コンストラクタ：`Some(v)`, `None`
  - 判定：`is_some(o)`, `is_none(o)`
  - 強制取得：`unwrap_option(o)`（None の場合は `panic`）

- Vec
  - `Vec(T)`: { T *data; usize len; usize cap; }
  - 作成：`vec_new(T)`, `vec_with_capacity(T, c)`
  - 操作：`vec_len(v)`, `vec_capacity(v)`, `vec_push(v, item)`, `vec_pop(v)`（`Option(T)` を返す）
  - 解放：`vec_free(v)`
  - 補助関数：`vec_grow`, `vec_try_pop`

- Stringヘルパー（`m_var.h` 実装側）
  - `string_new()`, `string_free()`, `string_from_slice()`, `string_push()`, `string_append()`, `string_as_slice()`

- その他
  - `panic(const char *msg)` — 致命的エラー発生時にプログラムを停止

...その他多数の機能を実装予定です！


### 例
以下は典型的な利用パターンです。短く示します。

#### 1) エラーを呼び出し元へ伝播する（Result）
```c++
Result helper(...) { /* 失敗ならErr(code)を返す */ }
Result caller(...) {
    Try(helper(...)); // helperがErrの場合、callerは即座に同じErrを返す
    return Ok();
}
```

#### 2) 値を返す関数（ResultOf(T)）
```c++
ResultOf(int) compute(...) {
    if (bad) return ErrVal(Status_Invalid);
    return OkVal(42);
}

ResultOf(int) use() {
    let x = TryVal(compute(...)); // エラーならそのままreturn ErrVal(...)
    return OkVal(x);
}
```

#### 3) 値が存在するかもしれない（Option）
```c++
Option(int) find(...) {
    if (found) return Some(value);
    return None;
}

Option(int) r = find(...);
if (is_some(r)) {
    let v = r.value;
}
```

#### 4) 可変文字列（String）
```c++
let s = string_new();
string_append(&s, str_lit("hello"));
string_push(&s, '!');
string_free(&s);
```

#### 5) 動的配列（Vec）
```c++
let v = vec_new(int);
vec_push(v, 1); // 失敗すると関数からErrを返す可能性あり
Option(int) p = vec_pop(v);
if (is_some(p)) printf("popped: %d", p.value);
vec_free(v);
```

そのほかの実用的な例は`example/`ディレクトリを参照してください。

### FAQ
Q: `Try`は何をしているの？

A: `Try(r)` は内部で`__auto_type _r = (r); if (_r.status != Status_Ok) return _r;`を行います。つまり失敗を見つけたらそのエラー`Result`を呼び出し元に即座に返します。

Q: `Option(T)`の`Some`はコピーされる？

A: はい。`Some(v)`は値をコピーして`Option`の`.value`に格納します。大きな構造体を入れるときは注意してください（必要ならポインタを入れる設計にする）。

Q: `vec_push` が失敗するとどうなる？

A: `vec_push`内で容量拡張に失敗した場合、`vec_grow`が`Err`を返します。そのマクロを使っている関数は早期リターンしてエラーを外に伝えます。

### ライセンス
[LICENSE](../LICENSE)を参照してください。