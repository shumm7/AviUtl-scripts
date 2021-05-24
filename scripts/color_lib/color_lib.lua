
local function split(str, delim)
    if string.find(str, delim) == nil then
        return { str }
    end

    local result = {}
    local pat = "(.-)" .. delim .. "()"
    local lastPos
    for part, pos in string.gfind(str, pat) do
        table.insert(result, part)
        lastPos = pos
    end
    table.insert(result, string.sub(str, lastPos))
    return result
end

local function loadCSV(dir)
	local p = ","
	local f = io.open(dir, "r")
	local res, t = {}, nil

	local cnt = 1
	for line in f:lines() do
		if cnt==1 then
			t = split(line, p)
			for k,v in pairs(t) do
				res[tostring(v)] = {}
			end

		else
			local s = split(line, p)
			for k,v in pairs(t) do
				table.insert(res[tostring(v)], s[k])
			end
		end
		cnt = cnt + 1
	end

	return res
end


function loadColorList(list)
	DATA_PATH = string.gsub(obj.getinfo("script_path").."color_lib\\list\\"..list..".csv", "\\", "/")
	return loadCSV(DATA_PATH)
end

function findColors(listName, string, mode, searchMode)
	if string==nil or string=="" then
		return
	end

	local res = {}
	DATA = loadColorList(list)

	if searchMode==0 then -- 完全一致
	for i=1, #mode do
		m=mode[i]
		for c=1, #DATA[m] do
			if DATA[m][c]==string then
				table.insert(res, {color=DATA["color"][c], name=DATA["name"][c], japanese=DATA["japanese"][c], english=DATA["english"][c]})
			end
		end
	end
	elseif searchMode==1 then -- 部分一致
		for i=1, #mode do
			m=mode[i]
			for c=1, #DATA[m] do
				s = DATA[m][c]:lower():find(string:lower())
				if s~=nil then
					table.insert(res, {color=DATA["color"][c], name=DATA["name"][c], japanese=DATA["japanese"][c], english=DATA["english"][c]})
				end
			end
		end
	elseif searchMode==2 then -- 前方一致
		for i=1, #mode do
			m=mode[i]
			for c=1, #DATA[m] do
				s = DATA[m][c]:find(string)
				if s==1 then
					table.insert(res, {color=DATA["color"][c], name=DATA["name"][c], japanese=DATA["japanese"][c], english=DATA["english"][c]})
				end
			end
		end
	elseif searchMode==3 then -- 後方一致
		for i=1, #mode do
			m=mode[i]
			for c=1, #DATA[m] do
				s = DATA[m][c]:find(string)
				if s==DATA[m][c]:len()-string:len()+1 then
					table.insert(res, {color=DATA["color"][c], name=DATA["name"][c], japanese=DATA["japanese"][c], english=DATA["english"][c]})
				end
			end
		end
	end

	return res
end

function findColor(listName, string, mode, searchMode)
	DATA = findColors(listName, string, mode, searchMode)
	if DATA==nil then
		return
	end
	if #DATA==0 then
		return
	end
	if #DATA==1 then
		return DATA[1]
	end

	l = string:len()
	diff, v = 100000, nil

	for i=1, #mode do
		m=mode[i]
		for c=1, #DATA do
			if DATA[c][m]:lower():find(string:lower())~= nil then
				t_diff = math.abs(l - DATA[c][m]:len())
				if t_diff==0 then
					return DATA[c]
				elseif t_diff<diff then
					diff = t_diff
					v = c
				end
			end
		end
	end

	return DATA[v]
end
