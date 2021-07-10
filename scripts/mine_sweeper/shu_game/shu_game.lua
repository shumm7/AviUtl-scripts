--[[

  shu_game.lua
	               v1.0 (2021-07-11)

]]


require("rikky_module")

local function getMouseInfo(rl)
	local mx, my = rikky_module.mouse()
	local c = nil
	if rl=="right" then
		c = rikky_module.key("RB")[1]
	else
		c = rikky_module.key("LB")[1]
	end

	if c == nil then
		return
	end

	local ret = {
		click = c,
		x = mx,
		y = my
	}
	return ret
end

local function setGlobalVariable(name, valiable)
	_G[name]=valiable
end

local function checkOnClicked(click, modeClick, rl)
	if rl=="right" then
		if mode_click==0 or mode_click==false then
			if click==false then
				if R_OnClickedFlag==false then
					return {OnClick=false, OnRelease=false}
				else
					_G["R_OnClickedFlag"] = false
					return {OnClick=false, OnRelease=true}
				end
			else
				if R_OnClickedFlag==false then
					_G["R_OnClickedFlag"] = true
					return {OnClick=true, OnRelease=false}
				else
					return {OnClick=false, OnRelease=false}
				end
			end

		elseif mode_click==1 or mode_click==true then
			if click==false then
				return {OnClick=false, OnRelease=false}
			else
				return {OnClick=true, OnRelease=true}
			end
		end

	else
		if mode_click==0 or mode_click==false then
			if click==false then
				if L_OnClickedFlag==false then
					return {OnClick=false, OnRelease=false}
				else
					_G["L_OnClickedFlag"] = false
					return {OnClick=false, OnRelease=true}
				end
			else
				if L_OnClickedFlag==false then
					_G["L_OnClickedFlag"] = true
					return {OnClick=true, OnRelease=false}
				else
					return {OnClick=false, OnRelease=false}
				end
			end

		elseif mode_click==1 or mode_click==true then
			if click==false then
				return {OnClick=false, OnRelease=false}
			else
				return {OnClick=true, OnRelease=true}
			end
		end
	end
end


return {
	getMouseInfo = getMouseInfo,
	setGlobalVariable = setGlobalVariable,
	checkOnClicked = checkOnClicked
}
