--[[
    GD50
    Breakout Remake

    -- PlayState Class --

    Author: Colton Ogden
    cogden@cs50.harvard.edu

    Represents the state of the game in which we are actively playing;
    player should control the paddle, with the ball actively bouncing between
    the bricks, walls, and the paddle. If the ball goes below the paddle, then
    the player should lose one point of health and be taken either to the Game
    Over screen if at 0 health or the Serve screen otherwise.
]]

PlayState = Class{__includes = BaseState}

--[[
    We initialize what's in our PlayState via a state table that we pass between
    states as we go from playing to serving.
]]
function PlayState:enter(params)
    self.paddle = params.paddle
    self.bricks = params.bricks
    self.health = params.health
    self.score = params.score
    self.highScores = params.highScores
    -- Balls
    self.ball = params.ball
    self.balls = {}
    self.ballsCount = 0
    table.insert(self.balls, self.ball)
    self.ballsCount = self.ballsCount + 1
    -- Key
    self.hasKey = params.hasKey
    -- Level
    self.level = params.level

    if params.recoverPoints ~= null then
        self.recoverPoints = params.recoverPoints
    else
        self.recoverPoints = 5000
    end

    -- Variables for powerup and combo
    self.powerups = {}
    self.comboCooldownTimer = 0
    self.startcomboCooldownTimer = false
    self.comboHitCount = 0 -- controls weather a powerup should spawn based on hitting the blocks 
    self.comboCount = 0 -- controls the comulative combo count
    self.showComboHitCount = false -- if should show the combo count
    self.powerupComboScore = 4 -- controls how much comboHits to get a powerup
    self.comboCooldownMaxTime = 1.5 -- max cooldown time seconds for getting combos

    -- give ball random starting velocity
    self.ball.dx = math.random(-200, 200)
    self.ball.dy = math.random(-80, -100)
end

function PlayState:update(dt)
    if self.paused then
        if love.keyboard.wasPressed('space') then
            self.paused = false
            gSounds['pause']:play()
        else
            return
        end
    elseif love.keyboard.wasPressed('space') then
        self.paused = true
        gSounds['pause']:play()
        return
    end

    -- update positions based on velocity
    self.paddle:update(dt)
    --self.ball:update(dt)

    -- COMBO AND POWERUP ---------------------------------------------------
    -- (START THE COMBO TIMER) start comboCooldownTimer if block has been hit
    if self.startcomboCooldownTimer then
        self.comboCooldownTimer = self.comboCooldownTimer + dt
    else
        self.comboCooldownTimer = 0
    end
    -- (MAKE COMBO VISIBLE) when ball collides 2 or more times and timer is still less than the max show the comboHitCount
    if self.comboHitCount >= 2 and self.comboCooldownTimer > 0 and self.comboCooldownTimer <= self.comboCooldownMaxTime then
        self.showComboHitCount = true
    end
    -- (RESET TIMER) if comboCooldownTimer is greater than or equal the max time reset the timer
    if self.comboCooldownTimer >= self.comboCooldownMaxTime then
        self.comboHitCount = 0
        self.comboCount = 0
        self.startcomboCooldownTimer = false
        self.showComboHitCount = false
    end
    -- (SPAWN POWERUP) create powerup (spawn) if combo hit count greater tha or equal combo score and timer is less than the max time
    if self.comboHitCount >= self.powerupComboScore and self.comboCooldownTimer <= self.comboCooldownMaxTime then
        table.insert(self.powerups, Powerup())
        self.comboHitCount = 0
    end
    -- (UPDATE POWERUPS) update and delete powerups if any
    for key, powerup in pairs(self.powerups) do
        powerup:update(dt)
        -- COLLIDES
        if powerup:collides(self.paddle) then
            gSounds['powerup']:play()

            if powerup.type == POWERUP_3BALL then
                for i = 1, 3, 1 do
                    ball = Ball(self.ball.skin)
                    ball.x = self.ball.x + math.random(-10, 10)
                    ball.y = self.ball.y + math.random(-10, 10)
                    ball.dx = self.ball.dx
                    ball.dy = self.ball.dy
                    table.insert(self.balls, ball)
                    self.ballsCount = self.ballsCount + 1
                end
            end

            if powerup.type == POWERUP_ADD_SINGLE_BALL then
                ball = Ball(self.ball.skin)
                ball.x = self.ball.x + math.random(-15, 15)
                ball.y = self.ball.y + math.random(-15, 15)
                ball.dx = self.ball.dx
                ball.dy = self.ball.dy
                table.insert(self.balls, ball)
                self.ballsCount = self.ballsCount + 1
            end

            if powerup.type == POWERUP_KEY then
                self.hasKey = true
                gSounds['powerup']:stop()
                gSounds['key']:play()
            end

            if powerup.type == POWERUP_HEALTH then
                self.health = math.min(3, self.health + 1)
                self.paddle.size = 3
                gSounds['powerup']:stop()
                gSounds['recover']:play()
            end

            -- destroy powerup
            table.remove(self.powerups, key)
        end
        -- DESTOY POWERUP ACTOR
        if powerup.y > VIRTUAL_HEIGHT then -- deallocate powerup if it exits the screen
            table.remove(self.powerups, key)
        end
    end
    -- update all balls
    for key, ball in pairs(self.balls) do
        ball:update(dt)
        if ball:collides(self.paddle) then
            -- raise ball above paddle in case it goes below it, then reverse dy
            ball.y = self.paddle.y - 8
            ball.dy = -ball.dy
            --
            -- tweak angle of bounce based on where it hits the paddle
            --

            -- if we hit the paddle on its left side while moving left...
            if ball.x < self.paddle.x + (self.paddle.width / 2) and self.paddle.dx < 0 then
                ball.dx = -50 + -(2 * (self.paddle.x + self.paddle.width / 2 - ball.x))
            
            -- else if we hit the paddle on its right side while moving right...
            elseif ball.x > self.paddle.x + (self.paddle.width / 2) and self.paddle.dx > 0 then
                ball.dx = 50 + (2 * math.abs(self.paddle.x + self.paddle.width / 2 - ball.x))
            end

            gSounds['paddle-hit']:play()
        end
    end
    -- -----------------------------------------------------------------------


    --[[if self.ball:collides(self.paddle) then
        -- raise ball above paddle in case it goes below it, then reverse dy
        self.ball.y = self.paddle.y - 8
        self.ball.dy = -self.ball.dy
        --
        -- tweak angle of bounce based on where it hits the paddle
        --

        -- if we hit the paddle on its left side while moving left...
        if self.ball.x < self.paddle.x + (self.paddle.width / 2) and self.paddle.dx < 0 then
            self.ball.dx = -50 + -(8 * (self.paddle.x + self.paddle.width / 2 - self.ball.x))
        
        -- else if we hit the paddle on its right side while moving right...
        elseif self.ball.x > self.paddle.x + (self.paddle.width / 2) and self.paddle.dx > 0 then
            self.ball.dx = 50 + (8 * math.abs(self.paddle.x + self.paddle.width / 2 - self.ball.x))
        end

        gSounds['paddle-hit']:play()
    end --]]

    -- detect collision across all bricks with the ball
    for k, brick in pairs(self.bricks) do

        -- only check collision if we're in play
        if brick.inPlay then
            for key, ball in pairs(self.balls) do
                if ball:collides(brick) then
                    -- check if brick is a key brick and if user has the key
                    if brick.color == 6 and brick.tier == 3 and not self.hasKey then
                        gSounds["brick-hit-1"]:stop()
                        gSounds["brick-hit-1"]:play()
                        goto continue
                    end

                   -- add to score
                    self.score = self.score + (brick.tier * 200 + brick.color * 25)

                    -- add to comboHitCount
                    self.comboHitCount = self.comboHitCount + 1
                    self.comboCount = self.comboCount + 1
                    if self.comboHitCount == 1 then
                        self.startcomboCooldownTimer = true
                    end
                    -- reset comboCooldownTimer in order to keep comboCooldownTimer running and allow to more combo points instead of resiting in a fixed time
                    self.comboCooldownTimer = 0

                    -- trigger the brick's hit function, which removes it from play
                    brick:hit()

                    -- if we have enough points, recover a point of health
                    if self.score >= self.recoverPoints then
                        -- can't go above 3 health
                        self.health = math.min(3, self.health + 1)

                        -- multiply recover points by 2
                        self.recoverPoints = self.recoverPoints * 2

                        -- play recover sound effect
                        gSounds['recover']:play()
                    end

                    -- go to our victory screen if there are no more bricks left
                    if self:checkVictory() then
                        gSounds['victory']:play()

                        gStateMachine:change('victory', {
                            level = self.level,
                            paddle = self.paddle,
                            health = self.health,
                            score = self.score,
                            highScores = self.highScores,
                            ball = self.ball,
                            recoverPoints = self.recoverPoints
                        })
                    end

                    ::continue::
                    --
                    -- collision code for bricks
                    --
                    -- we check to see if the opposite side of our velocity is outside of the brick;
                    -- if it is, we trigger a collision on that side. else we're within the X + width of
                    -- the brick and should check to see if the top or bottom edge is outside of the brick,
                    -- colliding on the top or bottom accordingly 
                    --

                    -- left edge; only check if we're moving right, and offset the check by a couple of pixels
                    -- so that flush corner hits register as Y flips, not X flips
                    if ball.x + 2 < brick.x and ball.dx > 0 then
                        
                        -- flip x velocity and reset position outside of brick
                        ball.dx = -ball.dx
                        ball.x = brick.x - 8
                    
                    -- right edge; only check if we're moving left, , and offset the check by a couple of pixels
                    -- so that flush corner hits register as Y flips, not X flips
                    elseif ball.x + 6 > brick.x + brick.width and ball.dx < 0 then
                        
                        -- flip x velocity and reset position outside of brick
                        ball.dx = ball.dx
                        ball.x = brick.x + 32
                    
                    -- top edge if no X collisions, always check
                    elseif ball.y < brick.y then
                        
                        -- flip y velocity and reset position outside of brick
                        ball.dy = -ball.dy
                        ball.y = brick.y - 8
                    
                    -- bottom edge if no X collisions or top collision, last possibility
                    else
                        
                        -- flip y velocity and reset position outside of brick
                        ball.dy = -ball.dy
                        ball.y = brick.y + 16
                    end

                    -- slightly scale the y velocity to speed up the game, capping at +- 150
                    if math.abs(ball.dy) < 150 then
                        ball.dy = ball.dy * 1.02
                    end

                    -- only allow colliding with one brick, for corners
                    break 
                end
            end
            
        end
        
    end

    -- if ball goes below bounds, revert to serve state and decrease health
    for key, ball in pairs(self.balls) do
        if ball.y >= VIRTUAL_HEIGHT then
            if self.ballsCount > 0 then
                self.ballsCount = self.ballsCount - 1
                table.remove(self.balls, key)
            end
            if self.ballsCount <= 0 then
                self.health = self.health - 1
                self.paddle.size = math.max(1, self.paddle.size - 1)
                gSounds['hurt']:play()

                if self.health == 0 then
                    gStateMachine:change('game-over', {
                        score = self.score,
                        highScores = self.highScores
                    })
                else
                    gStateMachine:change('serve', {
                        paddle = self.paddle,
                        bricks = self.bricks,
                        health = self.health,
                        score = self.score,
                        highScores = self.highScores,
                        level = self.level,
                        recoverPoints = self.recoverPoints,
                        hasKey = self.hasKey
                    })
                end
            end
        end
    end

    -- for rendering particle systems
    for k, brick in pairs(self.bricks) do
        brick:update(dt)
    end

    if love.keyboard.wasPressed('escape') then
        love.event.quit()
    end
end

function PlayState:render()
    -- render bricks
    for k, brick in pairs(self.bricks) do
        brick:render()
    end

    -- render all particle systems
    for k, brick in pairs(self.bricks) do
        brick:renderParticles()
    end

    self.paddle:render()
    self.ball:render()

    -- render all powerups
    for key, powerup in pairs(self.powerups) do
        powerup:render()
    end

    -- render all balls
    for key, ball in pairs(self.balls) do
        ball:render()
    end

    if self.showComboHitCount then
        love.graphics.setColor(1, 0.8, 0)
        love.graphics.setFont(gFonts['medium'])
        love.graphics.printf(
            "Combo " ..tostring(self.comboCount) ..tostring('x'),
            2, VIRTUAL_HEIGHT/2 - 8,
            VIRTUAL_HEIGHT, 'center'
        )
    end
    -- Show comboCooldownTimer
    love.graphics.setColor(1, 1, 1)
    love.graphics.setFont(gFonts['small'])
    love.graphics.printf(
        "combo cooldown:",
        5, 100,
        VIRTUAL_WIDTH, 'left'
    )
    love.graphics.setFont(gFonts["medium"])
    love.graphics.printf(
        tostring(truncateDecimal(self.comboCooldownTimer, 1)) .."s",
        5, 110,
        VIRTUAL_WIDTH, 'left'
    )
    love.graphics.setFont(gFonts["small"])
    love.graphics.printf(
        tostring("Balls: ") .. tostring(self.ballsCount) .."x",
        VIRTUAL_WIDTH - 40, 110,
        VIRTUAL_WIDTH, 'left'
    )
    love.graphics.printf(
        tostring("Points to recover: ") .. tostring(self.recoverPoints - self.score) .." points",
        VIRTUAL_WIDTH - 135, 125,
        VIRTUAL_WIDTH, 'left'
    )
    if self.hasKey then
        love.graphics.draw(
            gTextures['key'],
            VIRTUAL_WIDTH - 25, 90,
            0,
            0.01
        )
    end

    renderScore(self.score)
    renderHealth(self.health)

    -- pause text, if paused
    if self.paused then
        love.graphics.setFont(gFonts['large'])
        love.graphics.printf("PAUSED", 0, VIRTUAL_HEIGHT / 2 - 16, VIRTUAL_WIDTH, 'center')
    end
end

function PlayState:checkVictory()
    for k, brick in pairs(self.bricks) do
        if brick.inPlay then
            return false
        end
    end

    return true
end