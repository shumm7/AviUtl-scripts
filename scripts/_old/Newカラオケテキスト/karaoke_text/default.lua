data = {
	edgeBokeh = 10, --縁ぼかし
	edgeColor = { right="0x000000", left="0xffffff"}, --縁色
	gradColor = { right={"0xffffff", "0xffffff"}, left={"0x117ad7", "0x0f2d47"} }, --グラデーション色

	--値をオーバーライドしない場合は、nilを指定してください
	font = nil, --フォント名
	rubyOffset = {nil ,nil}, --ルビ位置調整
	align = nil, --左右寄せ（0～17）
	size = nil, --テキストのサイズ
	rubySize = nil, --ルビのサイズ
	edgeSize = nil, --縁のサイズ
	gradWidth = nil --グラデーションの幅
}
