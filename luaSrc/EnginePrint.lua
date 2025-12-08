function EngineLog(...)
    local args = {...}
    message = ": "
    for i, v in ipairs(args) do
        message = message ..v
    end
    print("[Lua LOG] " ..os.date("%H:%M:%S" ), message)
end