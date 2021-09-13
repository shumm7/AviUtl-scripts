local P = {}
local Extram = require("Extram")
local Buffermask = require("S_Buffermask_Module")

P.cache = {}

local function rot(r, x, y, sx, sy)
  if sx==nil then
    sx=0
  end
  if sy==nil then
    sy=0
  end

  local ax = x*math.cos(r) + y*-math.sin(r) + sx-sx*math.cos(r)+sy*math.sin(r)
  local ay = x*math.sin(r) + y*math.cos(r) + sy-sx*math.sin(r)-sy*math.cos(r)
  return ax, ay
end

function P.delete(key)
  local name = "Buffermask_"..tostring(key)
  Extram.del(name)
end

function P.store(key)
  local c = P.cache[key]
  local name = "Buffermask_"..tostring(key)

  local r = math.rad(obj.rz)
  local ax1, ay1 = rot(r, obj.w/2, -obj.h/2)
  local ax2, ay2 = rot(r, obj.w/2, obj.h/2)
  obj.setoption(
    "drawtarget",
    "tempbuffer",
    math.max(math.abs(ax1), math.abs(ax2)) * 2,
    math.max(math.abs(ay1), math.abs(ay2)) * 2
  )
  obj.draw(0, 0, 0, obj.zoom*obj.getvalue("zoom")/100, obj.alpha*obj.getvalue("alpha"), 0, 0, obj.rz)
  obj.load("tempbuffer")
  obj.rz = 0

  local data, w, h = obj.getpixeldata()
  Extram.put(name, data, w * 4 * h)

  if c== nil then
    c = {
      img = {}
    }
    P.cache[key] = c
  end
  if obj.w == 0 or obj.h == 0 then
    return
  end
  c.img = {
    w = w,
    h = h,
    ox = obj.ox,
    oy = obj.oy,
    oz = obj.oz,
    rx = obj.rx,
    ry = obj.ry,
    rz = obj.rz,
    cx = obj.cx,
    cy = obj.cy,
    cz = obj.cz,
    zoom = obj.zoom,
    alpha = obj.alpha,
    aspect = obj.aspect,
  }
end

function P.after(key, x, y, mode)
  local data, w, h = obj.getpixeldata()
  local name = "Buffermask_"..tostring(key)
  local cimg = P.cache[key].img

  obj.setoption("drawtarget", "tempbuffer", cimg.w, cimg.h)
  obj.load("tempbuffer")
  local mask_data, mask_w, mask_h = obj.getpixeldata("work")
  Extram.get(name, mask_data, mask_w * 4 * mask_h)

  Buffermask.ApplyMask(data, w, h, mask_data, mask_w, mask_h, x, y, mode, obj.check0)

  obj.setoption("drawtarget", "tempbuffer", w, h)
  obj.load("tempbuffer")
  obj.putpixeldata(data)
end

return P
