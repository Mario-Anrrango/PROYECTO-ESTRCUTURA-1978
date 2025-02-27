#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

struct FunctionData {
    string name;
    string complexity;
};

// Para representar los cambios de "factor" en un evento (para bucles)
struct ComplexityEvent {
    size_t pos;          // Posición en el cuerpo donde ocurre el evento
    int nExpDelta;       // Cambio en el exponente de n (ej. +1 para un bucle lineal)
    int logExpDelta;     // Cambio en el exponente de log n (ej. +1 para un bucle logarítmico)
    bool isStart;        // true = inicio del bucle; false = fin del bucle
};

// Convierte una cadena a minúsculas
string toLower(const string &str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Cuenta las ocurrencias de 'sub' en 'str'
int countOccurrences(const string &str, const string &sub) {
    int count = 0;
    size_t pos = 0;
    while ((pos = str.find(sub, pos)) != string::npos) {
        count++;
        pos += sub.size();
    }
    return count;
}

// Función auxiliar para encontrar la llave de cierre que corresponde a la llave de apertura en startPos
int findMatchingBrace(const string &body, size_t startPos) {
    int braceCount = 0;
    for (size_t i = startPos; i < body.size(); i++) {
        if (body[i] == '{')
            braceCount++;
        else if (body[i] == '}') {
            braceCount--;
            if (braceCount == 0)
                return i;
        }
    }
    return -1; // No se encontró
}

// Analiza el cuerpo de una función para determinar el máximo "producto" de factores de bucles anidados
// Devuelve un par (nExp, logExp)
pair<int,int> analyzeFunctionComplexity(const string &body) {
    // Expresión regular para detectar bucles for y while
    regex loopRegex("(for\\s*\\(.*?\\)|while\\s*\\(.*?\\))");
    auto beginIt = sregex_iterator(body.begin(), body.end(), loopRegex);
    auto endIt = sregex_iterator();
    
    vector<ComplexityEvent> events;
    
    for (auto it = beginIt; it != endIt; ++it) {
        smatch match = *it;
        size_t headerPos = match.position();
        string header = match.str();
        
        // Por defecto, asumimos bucle lineal: factor = (1,0)
        int factorN = 1;
        int factorLog = 0;
        // Si en el encabezado se detecta "/=" o ">>=", lo interpretamos como logarítmico
        if (header.find("/=") != string::npos || header.find(">>=") != string::npos) {
            factorN = 0;
            factorLog = 1;
        }
        
        // Buscar la llave de apertura '{' después del encabezado
        size_t openBracePos = body.find('{', headerPos);
        if (openBracePos == string::npos)
            continue;
        
        int closeBracePos = findMatchingBrace(body, openBracePos);
        if (closeBracePos == -1)
            continue;
        
        // Crear dos eventos: inicio y fin del bucle
        ComplexityEvent startEvent { openBracePos, factorN, factorLog, true };
        ComplexityEvent endEvent { (size_t)closeBracePos, factorN, factorLog, false };
        events.push_back(startEvent);
        events.push_back(endEvent);
    }
    
    // Ordenar los eventos por posición; en caso de empate, el de inicio tiene prioridad
    sort(events.begin(), events.end(), [](const ComplexityEvent &a, const ComplexityEvent &b) {
        if (a.pos == b.pos)
            return a.isStart && !b.isStart;
        return a.pos < b.pos;
    });
    
    int currentN = 0, currentLog = 0;
    int maxN = 0, maxLog = 0;
    
    // Barrido de eventos para determinar el máximo acumulado (anidamiento simultáneo)
    for (const auto &ev : events) {
        if (ev.isStart) {
            currentN += ev.nExpDelta;
            currentLog += ev.logExpDelta;
        }
        if (currentN > maxN || (currentN == maxN && currentLog > maxLog)) {
            maxN = currentN;
            maxLog = currentLog;
        }
        if (!ev.isStart) {
            currentN -= ev.nExpDelta;
            currentLog -= ev.logExpDelta;
        }
    }
    
    return make_pair(maxN, maxLog);
}

// Formatea el resultado en notación Big-O, por ejemplo O(n^a * (log n)^b)
string formatComplexity(pair<int,int> comp) {
    int nExp = comp.first;
    int logExp = comp.second;
    if (nExp == 0 && logExp == 0)
        return "O(1)";
    
    string result = "O(";
    bool needMultiply = false;
    if (nExp > 0) {
        result += "n";
        if (nExp > 1)
            result += "^" + to_string(nExp);
        needMultiply = true;
    }
    if (logExp > 0) {
        if (needMultiply)
            result += " * ";
        result += "log n";
        if (logExp > 1)
            result += "^" + to_string(logExp);
    }
    result += ")";
    return result;
}

// Función para extraer definiciones de funciones y calcular su complejidad
vector<FunctionData> ExtractFunctionsWithComplexity(const string &filename) {
    ifstream file(filename);
    vector<FunctionData> functions;
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        return functions;
    }
    
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    
    // Expresión regular para detectar definiciones de función (excluyendo sentencias de control)
    regex functionRegex(
        "^[ \\t]*(?!.*\\b(?:if|for|while|switch|else)\\b)[\\w:&*<>]+[ \\t]+((?:[a-zA-Z_][a-zA-Z0-9_]*::)*[a-zA-Z_][a-zA-Z0-9_]*)[ \\t]*\\([^\\)]*\\)[ \\t]*\\{"
    );
    
    for (size_t i = 0; i < lines.size(); i++) {
        smatch match;
        if (regex_search(lines[i], match, functionRegex)) {
            string functionName = match[1].str();
            // Extraer el cuerpo de la función contando llaves
            int braceCount = count(lines[i].begin(), lines[i].end(), '{') - count(lines[i].begin(), lines[i].end(), '}');
            string functionBody = lines[i] + "\n";
            size_t j = i + 1;
            while (j < lines.size() && braceCount > 0) {
                functionBody += lines[j] + "\n";
                braceCount += count(lines[j].begin(), lines[j].end(), '{');
                braceCount -= count(lines[j].begin(), lines[j].end(), '}');
                j++;
            }
            
            string complexityStr;
            string lowerName = toLower(functionName);
            
            // Detectar recursividad: si la función se llama a sí misma (más de una vez)
            int recursiveCount = countOccurrences(functionBody, functionName + "(");
            bool isRecursive = (recursiveCount > 1);
            
            // Caso especial: funciones de ordenamiento
            if (lowerName.find("sort") != string::npos) {
                complexityStr = "O(n log n)";
            } else {
                // Para otras funciones, usamos el análisis de bucles
                pair<int,int> comp = analyzeFunctionComplexity(functionBody);
                complexityStr = formatComplexity(comp);
            }
            
            // También, si se detecta recursividad en funciones no de sort, podrías ajustar
            // Por ejemplo, si la recursividad es evidente, podrías sobreescribir (esto es heurístico)
            // if (isRecursive && complexityStr == "O(1)") {
            //     complexityStr = "O(log n)";
            // }
            
            functions.push_back({functionName, complexityStr});
            i = j - 1; // Saltar las líneas ya procesadas
        }
    }
    return functions;
}

extern "C" __declspec(dllexport) void AnalyzeFunctions(const char* filename) {
    auto functions = ExtractFunctionsWithComplexity(filename);
    if (functions.empty()) {
        cout << "No se encontraron definiciones de funciones válidas en el archivo." << endl;
        return;
    }
    for (const auto &func : functions) {
        cout << "Función: " << func.name << " - Complejidad estimada: " << func.complexity << endl;
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
         case DLL_PROCESS_ATTACH:
         case DLL_THREAD_ATTACH:
         case DLL_THREAD_DETACH:
         case DLL_PROCESS_DETACH:
             break;
    }
    return TRUE;
}
