#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// Function to push an array of numbers to the Lua table
void push_array_to_lua(lua_State *L, int *array, int size) {
    lua_newtable(L);  // Create a new table in Lua
    for (int i = 0; i < size; i++) {
        lua_pushnumber(L, array[i]);  // Push the number
        lua_rawseti(L, -2, i + 1);     // Set it in the table
    }
}

int metatable() {
    lua_State *L = luaL_newstate();  // Create a new Lua state
    luaL_openlibs(L);                 // Load Lua libraries

    // Load the values.lua script
    if (luaL_dofile(L, "../lua/values-table.lua") != LUA_OK) {
        fprintf(stderr, "Error loading Lua file: %s\n", lua_tostring(L, -1));
        return 1;
    }


    // Create an instance of ValuesTable
    lua_getglobal(L, "ValuesTable");  // Get the ValuesTable class
    lua_getfield(L, -1, "new");       // Get the new method
    lua_call(L, 0, 1);                 // Call new(), returns instance
    lua_setglobal(L, "myValues");      // Set myValues in the global scope

    // Example array to add to Lua
    int array[] = {5, 3, 8, 1, 4};
    int size = sizeof(array) / sizeof(array[0]);

    // Add values from the C array to the Lua ValuesTable
    for (int i = 0; i < size; i++) {
        lua_getglobal(L, "myValues");   // Get myValues
        lua_getfield(L, -1, "add");      // Get the add method

        // Ensure that `add` is a function
        if (!lua_isfunction(L, -1)) {
            fprintf(stderr, "Error: 'add' is not a function\n");
            lua_pop(L, 1);  // Remove the non-function from the stack
            break;          // Exit the loop
        }

        // Push the value
        lua_pushnumber(L, array[i]);     // Push the value

        // Call add(value)
        if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
            fprintf(stderr, "Error calling add: %s\n", lua_tostring(L, -1));
            lua_pop(L, 1);  // Pop the error message
        }
    }

    // Retrieve the minimum value
    lua_getglobal(L, "myValues");       // Get myValues
    lua_getfield(L, -1, "min");         // Get the min method
    lua_call(L, 0, 1);                  // Call min()
    
    // Print the minimum value
    if (lua_isnumber(L, -1)) {
        printf("Minimum value: %.0f\n", lua_tonumber(L, -1));
    } else {
        printf("No values in the table.\n");
    }

    lua_close(L); // Close the Lua state
    return 0;
}
int async() {
    lua_State *L = luaL_newstate();  // Create a new Lua state
    luaL_openlibs(L);                 // Load Lua libraries

    // Load the coroutine.lua script
    if (luaL_dofile(L, "../lua/coroutine.lua") != LUA_OK) {
        fprintf(stderr, "Error loading Lua file: %s\n", lua_tostring(L, -1));
        lua_close(L);
        return 1;
    }

    // Call the runCoroutine function to execute the coroutine
    lua_getglobal(L, "runCoroutine"); // Get the runCoroutine function
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        fprintf(stderr, "Error calling runCoroutine: %s\n", lua_tostring(L, -1));
    }

    lua_close(L); // Close the Lua state
    return 0;
}
int hello() {
    lua_State *L = luaL_newstate();  // Create a new Lua state
    luaL_openlibs(L);                 // Load Lua libraries

    // Execute a Lua script
    luaL_dostring(L, "print('Hello from LuaJIT!')");

    lua_close(L);                     // Close the Lua state
    return 0;
}
int lua(int argc, char *argv[]){
    return metatable();
    //return async();
}