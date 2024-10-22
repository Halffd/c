-- values.lua

ValuesTable = {}
ValuesTable.__index = ValuesTable

-- Constructor
function ValuesTable.new()
    local self = setmetatable({}, ValuesTable)
    self.values = {}
    ptin("Made ", self)
    return self
end

-- Method to add a value
function ValuesTable:add(value)
    print(self.values, ' / ', self, ' / ', value)
    table.insert(self.values, value)
    print('Table: ', table)
end

-- Method to get the minimum value
function ValuesTable:min()
    print("Self ", #self, self)
    print("Values ", #self.values, self.values)
    if #self.values == 0 then return nil end
    local minValue = self.values[1]
    print("Min ", minValue)
    for _, v in ipairs(self.values) do
        print(_, ' . ', v)
        if v < minValue then
            minValue = v
        end
    end
    print(minValue)
    return minValue
end