enemy = {
    name = "Goblin",
    health = 30,
    attackPower = 5
}

function enemy.attack(playerHealth)
    print(enemy.name .. " attacks!")
    return playerHealth - enemy.attackPower
end

function enemy.onDamage(dmg)
    enemy.health = enemy.health - dmg
    print(enemy.name .. " took " .. dmg .. " damage! Health now: " .. enemy.health)
end