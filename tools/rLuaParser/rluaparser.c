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
    char *luaPushFuncs = (char *)calloc(1024*1024, 1);
    char *luaPushPtr = luaPushFuncs;
    int count = 0;

    while (!feof(rFile))
    {
        // Read one full line
        fgets(buffer, MAX_BUFFER_SIZE, rFile);
        
        if (buffer[0] == '/') fprintf(rluaFile, "%s", buffer);      // Direct copy of code comments
        else if ((buffer[0] == 'R') && 
                 (buffer[1] == 'L') &&
                 (buffer[2] == 'A') && 
                 (buffer[3] == 'P') && 
                 (buffer[0] == 'I'))            // raylib function declaration
        {
            char funcType[64];
            char funcName[64];
            char funcDesc[256];
            
            char params[128];
            char paramType[8][16];
            char paramName[8][32];
            
            sscanf(buffer, "RLAPI %s %[^(]s", funcType, funcName);
            
            //count++;
            //printf("Function processed %02i: %s\n", count, funcName);

            int index = 0;
            char *ptr = NULL;
 
            ptr = strchr(buffer, '(');
            
            if (ptr != NULL) index = (int)(ptr - buffer);
            else printf("Character not found!\n");
            
            sscanf(buffer + (index + 1), "%[^)]s", params);   // Read what's inside '(' and ')'  <-- CRASH after 128 iterations!
            
            ptr = strchr(buffer, '/');
            index = (int)(ptr - buffer);
            
            sscanf(buffer + index, "%[^\n]s", funcDesc);    // Read function comment after declaration
            
            fprintf(rluaFile, "%s\n", funcDesc);
            fprintf(rluaFile, "int lua_%s(lua_State *L)\n{\n", funcName);

            // Scan params string for number of func params, type and name
            char *paramPtr[16];         // Allocate 16 pointers for possible parameters
            int paramsCount = 0;
            paramPtr[paramsCount] = strtok(params, ",");
            
            bool funcVoid = (strcmp(funcType, "void") == 0);
            bool paramsVoid = false;

            while (paramPtr[paramsCount] != NULL)
            {
                sscanf(paramPtr[paramsCount], "%s %s\n", paramType[paramsCount], paramName[paramsCount]);
                
                if (strcmp(paramType[paramsCount], "void") == 0)
                {
                    paramsVoid = true;
                    break;
                }

                fprintf(rluaFile, "    %s %s = LuaGetArgument_%s(L, %i);\n", paramType[paramsCount], paramName[paramsCount], paramType[paramsCount], paramsCount + 1);
                
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

            count++;
            printf("Function processed %02i: %s\n", count, funcName);
            
            memset(buffer, 0, MAX_BUFFER_SIZE);
        }
        else if ((buffer[0] == 't') &&
                 (buffer[1] == 'y') &&
                 (buffer[2] == 'p') &&
                 (buffer[3] == 'e') &&
                 (buffer[4] == 'd') &&
                 (buffer[5] == 'e') &&
                 (buffer[6] == 'f'))            // raylib data type definition
        {
            char typeName[64];
            char typeDesc[256];
            
            int count = 0;
            char typeParamType[16][32] = {{ 0 }};
            char typeParamName[16][32] = {{ 0 }};
            char typeParamDesc[16][128] = {{ 0 }};

            sscanf(buffer, "typedef struct %s {", typeName);
            
            fgets(buffer, MAX_BUFFER_SIZE, rFile);      // Read one new full line
            
            while (buffer[0] != '}')   // Not closing structure type
            {
                if (buffer[0] != '\n')
                {
                    sscanf(buffer, "    %s %[^;]s %[^\n]s", &typeParamType[count][0], &typeParamName[count][0], &typeParamDesc[count][0]);
                    count++;
                }
                
                fgets(buffer, MAX_BUFFER_SIZE, rFile);  // Read one new full line
            }
            
            // Generate LuaGetArgument functions
            //-----------------------------------
            fprintf(rluaFile, "static %s LuaGetArgument_%s(lua_State *L, int index)\n{\n", typeName, typeName);
            fprintf(rluaFile, "    %s result = { 0 };\n", typeName);
            fprintf(rluaFile, "    index = lua_absindex(L, index); // Makes sure we use absolute indices because we push multiple values\n");
            for (int i = 0; i < count; i++)
            {
                // TODO: Consider different types (LUA_TNUMBER, LUA_TTABLE)
                fprintf(rluaFile, "    luaL_argcheck(L, lua_getfield(L, index, ""%s"") == LUA_TNUMBER, index, \"Expected %s.%s\");\n", typeParamName[i], typeName, typeParamName[i]);
                
                // TODO: Consider different data types (lua_tonumber, LuaGetArgument_Vector3)
                fprintf(rluaFile, "    result.%s = LuaGetArgument_%s(L, -1);\n", typeParamName[i], typeParamType[i]);
            }
            fprintf(rluaFile, "    lua_pop(L, %i);\n", count);
            fprintf(rluaFile, "    return result;}\n\n");
            
            // Generate LuaPush functions
            // NOTE: LuaPush functions are written in a separate string buffer, that will be written to file at the end
            //-----------------------------------
            int len = 0;
            len += sprintf(luaPushPtr + len, "static void LuaPush_%s(lua_State* L, %s obj)\n{\n", typeName, typeName);
            len += sprintf(luaPushPtr + len, "    lua_createtable(L, 0, %i);\n", count);
            for (int i = 0; i < count; i++)
            {
                len += sprintf(luaPushPtr + len, "    LuaPush_%s(L, obj.%s);\n", typeParamType[i], (typeParamName[i][0] == '*') ? (typeParamName[i] + 1) : typeParamName[i]);
                len += sprintf(luaPushPtr + len, "    lua_setfield(L, -2, \"%s\");\n", typeParamName[i]);
            }
            len += sprintf(luaPushPtr + len, "}\n\n");
            
            luaPushPtr += len;
        }
    }
    
    fprintf(rluaFile, "%s", luaPushFuncs);
    
    free(buffer);

    fclose(rFile);
    fclose(rluaFile);

    return 0;
}