local c = "0xbebebe"
data = {
	edgeBokeh = 10, --縁ぼかし
	edgeColor = { right="0x000000", left="0x000000"}, --縁色
	gradColor = { right={c, c}, left={c, c} }, --グラデーション色

	--値をオーバーライドしない場合は、nilを指定してください
	font = nil, --フォント名
	rubyOffset = {nil ,nil}, --ルビ位置調整
	align = nil, --左右寄せ（0～17）
	size = nil, --テキストのサイズ
	rubySize = nil, --ルビのサイズ
	edgeSize = nil, --縁のサイズ
	gradWidth = nil --グラデーションの幅
}
