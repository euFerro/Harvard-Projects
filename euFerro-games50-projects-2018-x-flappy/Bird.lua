--[[
    Bird Class
    Author: Colton Ogden
    cogden@cs50.harvard.edu

    The Bird is what we control in the game via clicking or the space bar; whenever we press either,
    the bird will flap and go up a little bit, where it will then be affected by gravity. If the bird hits
    the ground or a pipe, the game is over.
]]

Bird = Class{}

local GRAVITY = 7

function Bird:init()
    self.image = love.graphics.newImage('images/bird.png')
    self.x = VIRTUAL_WIDTH / 2 - 8
    self.y = VIRTUAL_HEIGHT / 2 - 8

    self.width = self.image:getWidth()
    self.height = self.image:getHeight()

    self.dy = 0
end

--[[
    AABB collision that expects a pipe, which will have an X and Y and reference
    global pipe width and height values.
]]
function Bird:collides(pipe)
    -- the 2's are left and top offsets
    -- the 4's are right and bottom offsets
    -- both offsets are used to shrink the bounding box to give the player
    -- a little bit of leeway with the collision
    if (self.x + 2) + (self.width - 4) >= pipe.x and self.x + 2 <= pipe.x + PIPE_WIDTH then
        if (self.y + 2) + (self.height - 4) >= pipe.y and self.y + 2 <= pipe.y + PIPE_HEIGHT then
            return true
        end
    end

    return false
end

function Bird:update(dt)
    self.dy = self.dy + GRAVITY * dt

    -- burst of anti-gravity when space or left mouse are pressed
    if love.keyboard.wasPressed('space') or love.mouse.wasPressed(1) then
        self.dy = -2.15
        sounds['jump']:play()
    end

    self.y = self.y + self.dy
end

function Bird:render()
    if self.dy <= -2 then -- If bird going up with a velocity equal or bigger than -2 make rotation bigger (in the comparison you have to check if it is smaller beacuse it`s a negative value)
        love.graphics.draw(self.image, self.x, self.y, -0.5, 1)
    elseif self.dy > -2 and self.dy < 0 then -- If it`s going up but slower make the rotaion smaller
        love.graphics.draw(self.image, self.x, self.y, -0.3, 1)
    elseif self.dy >= 0 and self.dy <= 1 then -- If it is still in the air or started to move a bit downward just dont rotate 
        love.graphics.draw(self.image, self.x, self.y, 0, 1)
    elseif self.dy> 1 and self.dy <= 2 then -- If it started to go down from zero to 1 rotate it a bit downwards
        love.graphics.draw(self.image, self.x, self.y, 0.3, 1)
    else -- If is going fast to the ground rortate the bird a lot
        love.graphics.draw(self.image, self.x, self.y, 0.5, 1)
    end
end