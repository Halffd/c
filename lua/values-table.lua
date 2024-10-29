-- values-table.lua

ValuesTable = {}
ValuesTable.__index = ValuesTable

-- Constructor
function ValuesTable.new()
    local self = setmetatable({}, ValuesTable)
    self.values = {}
    print("Created ValuesTable instance at:", self)
    return self
end

-- Method to add a value
function ValuesTable:add(value)
    print("Adding value:", value, "to table at:", self)
    table.insert(self.values, value)
    print("Current values:", self.values)
end

-- Method to get the minimum value
function ValuesTable:min()
    if #self.values == 0 then
        print("No values in the table.")
        return nil
    end
    local minValue = self.values[1]
    print("Initial min value:", minValue)

    for _, v in ipairs(self.values) do
        print("Checking value:", v)
        if v < minValue then
            minValue = v
        end
    end

    print("Minimum value found:", minValue)
    return minValue
end