/**********************************************************************************************

    rluaparser - raylib header parser to generate automatic Lua binding

    This parser scans raylib.h for functions that start with RLAPI and 
    generates raylib-lua function binding.

    Converts:
    RLAPI Color Fade(Color color, float alpha); // Color fade-in or fade-out, alpha goes from 0.0f to 1.0f

    To:
    // Color fade-in or fade-out, alpha goes from 0.0f to 1.0f
    int lua_Fade(lua_State* L)
    {
        Color arg1 = LuaGetArgument_Color(L, 1);
        float arg2 = LuaGetArgument_float(L, 2);
        Color result = Fade(arg1, arg2);
        LuaPush_Color(L, result);
        return 1;
    }
    
    Requirements to create binding raylib -> raylib-lua
    NOTE: "Type" refers to raylib defined structs (Vector2, Texture2D...)
        [ ] 1. Review LuaPush_Type defines/functions
        [ ] 2. Review LuaGetArgument_Type defines/functions
        [ ] 3. Review LuaIndexType functions (some raylib structs have changed)
        [ ] 4. Review lua_Type functions (raylib Lua structure constructors)
        [x] 5. Review function bindings (90% of raylib-lua.h code) --> DONE by this PARSER!
               NOTE: Some functions could require specific reviews
        [ ] 6. Review registered raylib lua functions --> REG()
        [ ] 7. Review enumerators setup on InitLuaDevice()

    LICENSE: zlib/libpng

    Copyright (c) 2018 Ramon Santamaria (@raysan5)

**********************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int main()
{
    #define MAX_BUFFER_SIZE     512

    FILE *rFile = fopen("raylib_test.h", "rt");
    FILE *rluaFile = fopen("raylib-lua_test.h", "wt");
    
    if ((rFile == NULL) || (rluaFile == NULL))
    {
        printf("File could not be opened.\n");
        return 0;
    }
    
    char *buffer = (char *)calloc(MAX_BUFFER_SIZE, 1);
    
    char *luaPushFuncs = (char *)calloc(1024*512, 1);   // 512 KB
    char *luaPushPtr = luaPushFuncs;
    
    char *luaREG = (char *)calloc(1024*256, 1);         // 256 KB
    char *luaREGPtr = luaREG;
    
    int funcsCount = 0;

    while (!feof(rFile))
    {
        // Read one full line
        fgets(buffer, MAX_BUFFER_SIZE, rFile);
        
        if (buffer[0] == '/') fprintf(rluaFile, "%s", buffer);      // Direct copy of code comments
        else if (strncmp(buffer, "RLAPI", 5) == 0)      // raylib function declaration
        {
            char funcType[64];
            char funcTypeAux[64];
            char funcName[64];
            char funcDesc[256];
            
            char params[128];
            char paramType[8][16];
            char paramName[8][32];
            
            sscanf(buffer, "RLAPI %s %[^(]s", funcType, funcName);
            
            if (strcmp(funcType, "const") == 0)
            {            
                sscanf(buffer, "RLAPI %s %s %[^(]s", funcType, funcTypeAux, funcName);
                strcpy(funcType, "string");
            }
            
            if ((funcName[0] == '*') && (funcName[1] == '*')) strcpy(funcName, funcName + 2);
            else if (funcName[0] == '*') strcpy(funcName, funcName + 1);

            int index = 0;
            char *ptr = NULL;
 
            ptr = strchr(buffer, '(');
            
            if (ptr != NULL) index = (int)(ptr - buffer);
            else printf("Character not found!\n");
            
            sscanf(buffer + (index + 1), "%[^)]s", params); // Read what's inside '(' and ')'  <-- CRASH after 128 iterations!
            
            ptr = strchr(buffer, '/');
            index = (int)(ptr - buffer);
            
            sscanf(buffer + index, "%[^\n]s", funcDesc);    // Read function comment after declaration

            // Generate Lua function lua_FuncName()
            //---------------------------------------
            fprintf(rluaFile, "%s\n", funcDesc);

            fprintf(rluaFile, "int lua_%s(lua_State *L)\n{\n", funcName);

            // Scan params string for number of func params, type and name
            char *paramPtr[16];         // Allocate 16 pointers for possible parameters
            int paramsCount = 0;
            paramPtr[paramsCount] = strtok(params, ",");
            
            bool funcVoid = (strcmp(funcType, "void") == 0);
            bool paramsVoid = false;
            char paramConst[8][16];
            
            int len = 0;

            while (paramPtr[paramsCount] != NULL)
            {
                sscanf(paramPtr[paramsCount], "%s %s\n", paramType[paramsCount], paramName[paramsCount]);
                
                if (paramName[paramsCount][0] == '*') strcpy(paramName[paramsCount], paramName[paramsCount] + 1);
                
                if (strcmp(paramType[paramsCount], "void") == 0)
                {
                    paramsVoid = true;
                    break;
                }

                if (strcmp(paramType[paramsCount], "const") == 0)
                {
                    sscanf(paramPtr[paramsCount], "%s %s %s\n", paramConst[paramsCount], paramType[paramsCount], paramName[paramsCount]);
                    
                    if (paramName[paramsCount][0] == '*') strcpy(paramName[paramsCount], paramName[paramsCount] + 1);
                    
                    fprintf(rluaFile, "    %s %s %s = LuaGetArgument_%s(L, %i);\n", paramConst[paramsCount], paramType[paramsCount], paramName[paramsCount], (strcmp(paramType[paramsCount], "char") == 0) ? "string" : paramType[paramsCount], paramsCount + 1);
                }
                else if (strcmp(paramType[paramsCount], "unsigned") == 0)
                {
                    sscanf(paramPtr[paramsCount], "%s %s %s\n", paramConst[paramsCount], paramType[paramsCount], paramName[paramsCount]);
                    
                    if (paramName[paramsCount][0] == '*') strcpy(paramName[paramsCount], paramName[paramsCount] + 1);
                    
                    fprintf(rluaFile, "    %s %s %s = LuaGetArgument_%s(L, %i);\n", paramConst[paramsCount], paramType[paramsCount], paramName[paramsCount], paramConst[paramsCount], paramsCount + 1);
                }
                //else if (strcmp(paramType[paramsCount], "...") == 0) 
                else fprintf(rluaFile, "    %s %s = LuaGetArgument_%s(L, %i);\n", paramType[paramsCount], paramName[paramsCount], paramType[paramsCount], paramsCount + 1);
                
                paramsCount++;
                paramPtr[paramsCount] = strtok(NULL, ",");
            }

            if (funcVoid) fprintf(rluaFile, "    %s(", funcName);
            else fprintf(rluaFile, "    %s result = %s(", funcType, funcName);
            
            if (!paramsVoid)
            {
                for (int i = 0; i < paramsCount - 1; i++) fprintf(rluaFile, "%s, ", paramName[i]);
                fprintf(rluaFile, "%s", paramName[paramsCount - 1]);
            }
            
            fprintf(rluaFile, ");\n");

            if (!funcVoid) fprintf(rluaFile, "    LuaPush_%s(L, result);\n", funcType);

            fprintf(rluaFile, "    return %i;\n}\n\n", funcVoid ? 0:1);

            fflush(rluaFile);

            funcsCount++;
            printf("Function processed %02i: %s\n", funcsCount, funcName);
            
            memset(buffer, 0, MAX_BUFFER_SIZE);
            
            // Register function names REG() into luaREG string
            //--------------------------------------------------
            len += sprintf(luaREGPtr + len, "REG(%s)\n", funcName);
            luaREGPtr += len;
            
        }
        else if (strncmp(buffer, "typedef", 7) == 0)    // raylib data type definition
        {
            char typeName[64];
            char typeDesc[256];
            
            int paramsCount = 0;
            char paramTypes[16][32] = {{ 0 }};
            char paramNames[16][32] = {{ 0 }};
            char paramDescs[16][128] = {{ 0 }};
            
            if (strncmp(buffer + 8, "struct", 6) == 0)
            {
                

                sscanf(buffer, "typedef struct %s {", typeName);
                
                fgets(buffer, MAX_BUFFER_SIZE, rFile);      // Read one new full line
                
                while (buffer[0] != '}')   // Not closing structure type
                {
                    if (buffer[0] != '\n')
                    {
                        sscanf(buffer, "    %s %[^;]s %[^\n]s", &paramTypes[paramsCount][0], &paramNames[paramsCount][0], &paramDescs[paramsCount][0]);
                        paramsCount++;
                    }
                    
                    fgets(buffer, MAX_BUFFER_SIZE, rFile);  // Read one new full line
                }
                
                // Generate LuaGetArgument functions
                //-----------------------------------
                fprintf(rluaFile, "static %s LuaGetArgument_%s(lua_State *L, int index)\n{\n", typeName, typeName);
                fprintf(rluaFile, "    %s result = { 0 };\n", typeName);
                fprintf(rluaFile, "    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values\n");
                for (int i = 0; i < paramsCount; i++)
                {
                    // TODO: Consider different types (LUA_TNUMBER, LUA_TTABLE)
                    fprintf(rluaFile, "    luaL_argcheck(L, lua_getfield(L, index, \"%s\") == LUA_TNUMBER, index, \"Expected %s.%s\");\n", paramNames[i], typeName, paramNames[i]);
                    
                    // TODO: Consider different data types (lua_tonumber, LuaGetArgument_Vector3)
                    fprintf(rluaFile, "    result.%s = LuaGetArgument_%s(L, -1);\n", paramNames[i], paramTypes[i]);
                }
                fprintf(rluaFile, "    lua_pop(L, %i);\n", paramsCount);
                fprintf(rluaFile, "    return result;\n}\n\n");
            
                // Generate LuaPush functions
                // NOTE: LuaPush functions are written in a separate string buffer, that will be written to file at the end
                //-----------------------------------
                int len = 0;
                len += sprintf(luaPushPtr + len, "static void LuaPush_%s(lua_State* L, %s obj)\n{\n", typeName, typeName);
                len += sprintf(luaPushPtr + len, "    lua_createtable(L, 0, %i);\n", paramsCount);
                for (int i = 0; i < paramsCount; i++)
                {
                    len += sprintf(luaPushPtr + len, "    LuaPush_%s(L, obj.%s);\n", paramTypes[i], (paramNames[i][0] == '*') ? (paramNames[i] + 1) : paramNames[i]);
                    len += sprintf(luaPushPtr + len, "    lua_setfield(L, -2, \"%s\");\n", paramNames[i]);
                }
                len += sprintf(luaPushPtr + len, "}\n\n");
                
                luaPushPtr += len;
            }
            else if (strncmp(buffer + 8, "enum", 4) == 0)
            {
                //sscanf(buffer, "typedef enum {");
                //printf("enum detected!\n");

                fgets(buffer, MAX_BUFFER_SIZE, rFile);      // Read one new full line
                fprintf(rluaFile, "LuaStartEnum();\n");
                
                while (buffer[0] != '}')   // Not closing structure type
                {
                    if (buffer[0] != '\n')
                    {
                        sscanf(buffer, "    %s", &paramNames[paramsCount][0]);
                        fprintf(rluaFile, "LuaSetEnum(\"%s\", %s);\n", &paramNames[paramsCount][0], &paramNames[paramsCount][0]);
                        paramsCount++;
                    }
                    
                    fgets(buffer, MAX_BUFFER_SIZE, rFile);  // Read one new full line
                }
                fprintf(rluaFile, "LuaEndEnum(\"name\");\n");
            }
        }
    }
    
    fprintf(rluaFile, "%s", luaPushFuncs);
    fprintf(rluaFile, "// raylib Functions (and data types) list\nstatic luaL_Reg raylib_functions[] = {\n");
    fprintf(rluaFile, "%s\n", luaREG);
    fprintf(rluaFile, "    { NULL, NULL }  // sentinel: end signal\n};");

    free(buffer);
    free(luaPushFuncs);
    free(luaREG);

    fclose(rFile);
    fclose(rluaFile);

    return 0;
}