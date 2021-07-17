-----------------------------------------------------
--　data変数で、本体側から引数を受け取ることが出来ます。
-----------------------------------------------------
function number(str)
	local ret = tonumber(str)
	if ret==nil then
		return 100
	end
	return ret
end

local size = number(data[1])/100
local sx, sy = number(data[2])/100, number(data[3])/100
local px, py = obj.w*size*sx, obj.h*size*sy

obj.setoption("drawtarget","tempbuffer", px, py)
obj.drawpoly(-px/2, -py/2, 0, px/2, -py/2, 0, px/2, py/2, 0, -px/2, py/2, 0, 0, 0, obj.w, 0, obj.w, obj.h, 0, obj.h)
obj.setoption("drawtarget","framebuffer")
obj.load("tempbuffer")

-----------------------------------------------------
--　以下の形式で、スクリプトの説明をreturnします
-----------------------------------------------------
return {
	main = "拡大縮小を行います。",
	data1 = "拡大率",
	data2 = "X",
	data3 = "Y",
	data4 = ""
}
