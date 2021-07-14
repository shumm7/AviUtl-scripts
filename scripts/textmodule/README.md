# textmodule.dllについて
`textmodule.dll`は、Lua（ANSI）で`string.gsub`などを使用すると、不具合が発生する問題を解決したモジュールです。

具体的には、以下のようなフローで処理しています。  
1. Luaからマルチバイト文字列を`textmodule.dll`が受け取る。
2. `textmodule.dll`上でワイド文字列（Unicode）に変換
3. 文字列処理を行う
4. `textmodule.dll`上でマルチバイト文字列に変換
5. Luaに返す

## 引数・返り値について
文字列の位置は、1から順に数えます。  
例：`"abcdefg"`の`c`は3文字目  

文字数は、ワイド文字列の状態で計算します。  
例：`あいうえお`の長さは5  

## 更新履歴
- [2021-06-04]0.0.1
 - Release
- [2021-06-19]0.0.2
 - byte、char、gmatch、hiragana、katakana、halfwidth、fullwidth関数の追加
 - 引数入力時の処理を修正
- [2021-06-29]0.0.3
 - getinfo、time、date関数の追加
- [2021-07-06]0.1.0
 - utf8_byte、utf8_char関数の追加
- [2021-07-07]0.1.1
 - 開発環境をC++20へ移行
 - 例外時の処理を修正
 - date関数の処理を修正
- [2021-07-08]0.1.2
 - mojibake関数の追加
 - ソースファイルを分割
- [2021-07-14]0.1.3
 - debug_print関数の追加

## 関数
### `start, end = find(string, pattern)`
`string`にある`pattern`を検索し、その開始位置と終了位置を返します。  
ただし、`pattern`は正規表現です。  

### `t = sub(string, start, end)`
`string`の`start`文字目から`end`文字目までを返します。  
`end`を省略した場合、`start`文字目～最後までを切り抜きます。  

### `t = gsub(string, pattern, repl, num)`
`string`にある`pattern`を`repl`で置換します。  
ただし、`pattern`は正規表現です。  
`num`で置換の回数を指定しますが、指定しない場合は`1`になります。  

### `l = len(string)`
`string`の長さを返します。  
ワイド文字列においての長さであるため、Lua標準の`string.len`とは値が異なります。  

### `t = reverse(string)`
`string`を逆順にした文字列を返します。  
例：「あいうえお」→「おえういあ」  

### `t = upper(string)`
`string`内の英語小文字を大文字に変換して返します。

### `t = lower(string)`
`string`内の英語大文字を小文字に変換して返します。  

### `t = match(string, pattern, num)`
`string`と`pattern`を比較して、最初にマッチした部分を返します。  
ただし、`pattern`は正規表現です。  
`num`で検索を開始する位置を指定できますが、指定しない場合は`1`になります。  

### `t = byte(string, i, j)`
文字列`string`の`i`文字目から`j`文字目の文字コードを返します。  
文字コードの数値は、ワイド文字列の状態で取得します。  
`i`を指定しない場合は、`1`になります。  
`j`を指定しない場合は、`i`と同じ値になります。

### `t = char(i1, i2, ...)`
0個以上の数値 `i1, i2 ...` を指定すると、 各文字が与えられた引数と等しい内部コードを持ち、長さが引数の数に等しい、文字列を返します。   
文字コードの数値は、ワイド文字列の状態で取得します。  

### `func = gmatch(string, pattern)`
`string`から`pattern`に当てはまる部分を次々と返すような、イテレータ関数を返します。
ただし、`pattern`は正規表現です。   

### `t = hiragana(string)`
`string`内のカタカナをひらがなに変換して、返します。  

### `t = katakana(string)`
`string`内のひらがなをカタカナに変換して、返します。  

### `t = halfwidth(m)`
`string`内の全角文字を半角文字に変換して、返します。  
`m`（ブーリアン値）を指定すると、全角スペースを半角スペースに変換するかどうかを指定できます。
`m`を指定しない場合は、`true`となります。  

### `t = fullwidth(m)`
`string`内の半角文字を全角文字に変換して、返します。  
`m`（ブーリアン値）を指定すると、半角スペースを全角スペースに変換するかどうかを指定できます。
`m`を指定しない場合は、`true`となります。  

### `t = mojibake(string)`
文字列`string`を文字化けさせます。  
`string`をUTF-8に変換し、それをShift JISとして扱うことで文字化けさせています。  
改行`\n`などの特殊な記号の一部は無視されます。  
その仕様上、半角英数字などのASCII文字は基本的には文字化けしません。  

### `info = getinfo(str, index)`
textmoduleの情報を取得します。  
`index`を指定しない場合は、`1`となります。  

- `str="name"` モジュールの名前（例：`textmodule`）  
- `str="version"`  
 - `index=1` textmoduleのバージョン（例：`0.0.3`）  
 - `index=2` textmoduleのバージョンの通し番号（例：`3`）  

### `t = time(table)`
テーブル`table`で指定された時刻を表す数値を返します。  
`nil`もしくはなにも指定しない場合は、現在時刻を返します。  
`table`には最低限`year`、`month`、`day`の要素がなければなりません。
テーブルの構造は、下記の`date`関数の項目を確認してください。

### `t = date(format, time)`
時間を表す数値`time`を`format`をもとに、文字列へ変換します。  
`format`の書式は[こちら](https://cpprefjp.github.io/reference/chrono/format.html)を参照してください。  

`format`が`"*t"`のときは、以下の構造で表されるテーブルで値を返します。  
ただし、`format`の先頭1文字が`"!"`の場合は、UTC（世界協定時刻）で計算します。  

#### テーブルの構造
- `year` 年
- `month` 月
- `day` 日
- `hour` 時間
- `min` 分
- `sec` 秒
- `wday` 曜日（1が月曜日）
- `yday` 年内の通し日数（1-366）
- `isdst` 夏時間フラグ（数値）

### `t = utf8_byte(string, i, j)`
文字列`string`の`i`文字目から`j`文字目の文字コードを返します。  
文字コードの数値は、UTF-8で取得します。  
`i`を指定しない場合は、`1`になります。  
`j`を指定しない場合は、`i`と同じ値になります。

### `t = utf8_char(i1, i2, ...)`
0個以上の数値 `i1, i2 ...` を指定すると、 各文字が与えられた引数と等しいUTF-8符号を持ち、長さが引数の数に等しい、文字列を返します。   
文字コードの数値は、ワイド文字列の状態で取得します。  

### `t = debug_print(...)`
0個以上の引数を指定すると、それらを文字列に変換し、`aaa,1234,true`のように`,`区切りで連結し返します。  
またこの文字列を`OutputDebugString()`に送ります。  
デバッグ用に使用することが出来ます。  
`string`、`number`、`boolean`以外の型の引数は、その型名が表示されます。  
