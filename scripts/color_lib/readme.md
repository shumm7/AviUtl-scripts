# color_libについて
color_libは、AviUtl上で「色」をより便利に使用するためのライブラリです。  

## 環境
color_lib v0.2  
このスクリプト・プラグインはこちらの環境でテストされています。   
　AviUtl 1.10 / exedit 0.93rc1

## ファイルについて
- `color_lib.dll`：color_libの本体
- `@color_lib.obj`：color_lib.dllを使用したスクリプトなど
- `color_lib`フォルダ：color_lib.dllが使用するデータを保存する場所

### 色リスト
`color_lib/color_list/`に色リストを保存したCSVファイルが存在しています。  
はじめから6つのファイルがありますが、これに加えて、任意の色リストを作成することができます。  
詳細は`_about.md`をご確認ください。  

## color_lib.dllの関数
### `getColorList(path)`  
`path`で指定したCSVファイルの色リストをテーブルで取得します。  
```Lua
col = getColorList("C:/aviutl/script/color_lib/color_list/jis.csv")  
debug_print(col[3].color)
```

### `searchColors(path, word, searchPos, mode)`
`path`で指定したCSVファイルの色リストから、`word`を元に検索した色リストをテーブルで取得します。  
`searchPos`で検索に使用する列を指定します（例：`"name,english"`）。  
`mode`で検索方法を指定します（`0`:完全一致　`1`:部分一致　`2`:前方一致　`3`:後方一致）。    
```Lua
col = searchColors("C:/aviutl/script/color_lib/color_list/jis.csv", "red", "name,japanese,english", 1)  
for i=1,#col do
	debug_print(col[i].color..":"..col[i].name)
end
```

### `searchColor(path, word, searchPos, mode)`
上記`searchColor`で得た結果から、最も`word`と近い色を1つ取得します。  
ただし、取得した色は要素数が1のテーブルであることに注意してください。  
```Lua
col = searchColor("C:/aviutl/script/color_lib/color_list/jis.csv", "blue", "name,japanese,english", 1)  
debug_print(col[1].color..":"..col[1].name)
```
