--[[
    Class made by Breno Ferro GD50 breakout assignment
]]
Powerup = Class{}

POWERUP_HEALTH = 3
POWERUP_3BALL = 4
POWERUP_ADD_SINGLE_BALL = 9
POWERUP_KEY = 10

powerup_types = {
    [1] = POWERUP_HEALTH,
    [2] = POWERUP_3BALL,
    [3] = POWERUP_ADD_SINGLE_BALL,
    [4] = POWERUP_KEY
}

function Powerup:init()
    self.width = 16
    self.height = 16
    self.type = powerup_types[math.random(4)] -- generates one of the four powerup types
    self.gravity = 50
    -- Spawns powerup in a random x position
    self.x = VIRTUAL_WIDTH * math.random()
    -- Spawns powerup in a random y position
    self.y = VIRTUAL_HEIGHT * math.random() - 150 -- y offset so powerup spwans at the bottom

    -- ajust x and y positions if it has passed the left or right of the screen so it appears correclty
    if self.x <= 0 then
        self.x = self.width
    elseif self.x >= VIRTUAL_WIDTH then
        self.x = VIRTUAL_WIDTH - self.width
    end
end

function Powerup:collides(target)
    -- If right left edge is farther to the right than the rigth edge of the other 
    if self.x > target.x + target.width or target.x > self.x + self.width then
        return false
    end 
    -- If bottom
    if self.y > target.y + target.height or target.y > self.y + self.height then
        return false
    end
    -- If target(object) is colliding
    return true
end

function Powerup:update(dt)
    self.y = self.y + self.gravity * dt
end

function Powerup:render()
    love.graphics.draw(
        gTextures['main'],
        gFrames['powerups'][self.type],
        self.x, self.y
    )
    --love.graphics.printf("Powerup.y = "..tostring(self.y) .." x= " ..tostring(self.x) .." gravity= "..tostring(self.gravity) .." skin= " .. tostring(self.skin), 0, VIRTUAL_HEIGHT/2, VIRTUAL_WIDTH, 'right')
end