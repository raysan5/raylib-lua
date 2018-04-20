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
        [ ] 1. Review LuaPush_Type defines
        [ ] 2. Review LuaGetArgument_Type defines/functions
        [ ] 3. Review LuaPush_Type functions
        [ ] 4. Review LuaIndexType functions (some raylib structs have changed)
        [ ] 5. Review lua_Type functions (raylib Lua structure constructors)
        [x] 6. Review function bindings (90% of raylib-lua.h code) --> DONE by this PARSER!
               NOTE: Some functions could require specific reviews
        [ ] 7. Review registered raylib lua functions --> REG()
        [ ] 8. Review enumerators setup on InitLuaDevice()

    LICENSE: zlib/libpng

    Copyright (c) 2018 Ramon Santamaria (@raysan5)

**********************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    #define MAX_BUFFER_SIZE     512

    char buffer[MAX_BUFFER_SIZE];

    FILE *rFile = fopen("raylib_test.h", "rt");
    FILE *rluaFile = fopen("raylib-lua_test.h", "wt");
    
    if ((rFile == NULL) || (rluaFile == NULL))
    {
        printf("File could not be opened.\n");
        return 0;
    }

    while (!feof(rFile))
    {
        // Read one full line
        fgets(buffer, MAX_BUFFER_SIZE, rFile);
        
        if (buffer[0] == '/') fprintf(rluaFile, "%s", buffer);  // Direct copy of code comments
        else if ((buffer[0] == 'R') && (buffer[1] == 'L') && (buffer[2] == 'A') && (buffer[3] == 'P') && (buffer[4] == 'I'))
        {
            char funcType[8];
            char funcName[32];
            char funcDesc[256];
            
            char params[128];
            char paramType[8][16];
            char paramName[8][32];
            
            sscanf(buffer, "RLAPI %s %[^(]s", funcType, funcName);
            
            char *ptr;
            int index;

            ptr = strchr(buffer, '(');
            index = (int)(ptr - buffer);
            
            sscanf(&buffer[index + 1], "%[^)]s", params);   // Read what's inside '(' and ')'
            
            ptr = strchr(buffer, '/');
            index = (int)(ptr - buffer);
            
            sscanf(&buffer[index], "%[^\n]s", funcDesc);    // Read function comment after declaration
            
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
        }
    }

    fclose(rFile);
    fclose(rluaFile);

    return 0;
}