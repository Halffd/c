-- coroutine.lua

-- Coroutine function to execute nested loops
function loopCoroutine()
    for i = 1, 100 do
        for j = 1, 100 do
            -- Yield to allow other coroutines to run
            coroutine.yield(i, j)
        end
    end
    return "Completed"  -- Return a completion message
end

-- Create a coroutine
local co = coroutine.create(loopCoroutine)

-- Function to run the coroutine and print results
function runCoroutine()
    while coroutine.status(co) ~= 'dead' do
        local success, i, j = coroutine.resume(co)
        if success then
            if i and j then 
                print("i: " .. i .. ", j: " .. j)
            end
        else
            print("Coroutine error: " .. i)
        end
    end
    
    -- Check for completion message
    if coroutine.status(co) == 'dead' then
        print("Coroutine finished successfully.")
    end
end