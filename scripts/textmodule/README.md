# textmodule.dllについて
`textmodule.dll`は、Lua（ANSI）で`string.gsub`などを使用すると、不具合が発生する問題を解決したモジュールです。

具体的には、以下のようなフローで処理しています。  
1. Luaからマルチバイト文字列を`textmodule.dll`が受け取る。
2. `textmodule.dll`上でワイド文字列に変換
3. 文字列処理を行う
4. `textmodule.dll`上でマルチバイト文字列に変換
5. Luaに返す

## 引数・返り値について
文字列の位置は、1から順に数えます。  
例：`"abcdefg"`の`c`は3文字目  

文字数は、ワイド文字列の状態で計算します。  
例：`あいうえお`の長さは5  


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
例：「あいうえお」→「おえいうあ」  

### `t = upper(string)`
`string`内の英語小文字を大文字に変換して返します。

### `t = lower(string)`
`string`内の英語大文字を小文字に変換して返します。  

### `t = match(string, pattern, num)`
`string`と`pattern`を比較して、最初にマッチした部分を返します。  
ただし、`pattern`は正規表現です。  
`num`で検索を開始する位置を指定できますが、指定しない場合は`1`になります。  
