//Copyright (c) 2011 Oscar (.teri) Triano <teritriano@gmail.com>

//Permission is hereby granted, free of charge, to any person obtaining a 
//copy of this software and associated documentation files (the "Software"), 
//to deal in the Software without restriction, including without limitation the rights to use, 
//copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
//and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included 
//in all copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
//OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
//THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR 
//OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
//ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
//OTHER DEALINGS IN THE SOFTWARE.

#include <stdio.h>
#include <string.h>
#include <lunatic_chipmunk.h>

int chipmunk_NewSpace(lua_State *vm){
    cpSpace *space = lua_newuserdata(vm, sizeof(cpSpace));
    cpSpaceInit(space);
    lua_getfield(vm, LUA_REGISTRYINDEX, "chipmunk.spacemeta");
    lua_setmetatable(vm, -2);
    return 1;
}

int chipmunk_space_newindex(lua_State *vm){
    cpSpace *space = (cpSpace *)lua_touserdata(vm, 1);
    const char *key = lua_tostring(vm, 2);
    if (strcmp("gravity", key) == 0 && lua_istable(vm, 3)){
        cpSpaceSetGravity(space, chipmunk_TableTocpVect(3, vm));
    }
    return 0;
}

int chipmunk_space_index(lua_State *vm){
    cpSpace *space = (cpSpace *)lua_touserdata(vm, 1);
    const char *key = lua_tostring(vm, 2);
    if (strcmp("gravity", key) == 0){
        chipmunk_cpVectToTable(cpSpaceGetGravity(space), vm);
        return 1;
    }
    lua_getfield(vm, LUA_REGISTRYINDEX, "chipmunk.space:");
    lua_getfield(vm, -1, key);
    return 1;
}

int chipmunk_space_gc(lua_State *vm){
    cpSpace *space = (cpSpace *)lua_touserdata(vm, 1);
    cpSpaceDestroy(space);
    printf("Delete space: %p\n", space);
}

int chipmunk_space_Step(lua_State *vm){
    //space, number
    cpSpace *space = (cpSpace *)lua_touserdata(vm, 1);
    cpSpaceStep(space, lua_tonumber(vm, 2));
    return 0;
}

int chipmunk_space_AddBody(lua_State *vm){
    //space, body
    cpSpace *space = lua_touserdata(vm, 1);
    cpBody *body = lua_touserdata(vm, 2);
    cpSpaceAddBody(space, body);
    return 0;
}
