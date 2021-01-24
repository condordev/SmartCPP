#include <iostream>          // Ein und Ausgabe
#include <string>            // C++-Strings
#include <cstring>           // Vergleiche von C-Strings

using namespace std;

// Unsere Standardvorlage für maxi()
template <typename T>
T maxi(T obj1, T obj2) {
    if (obj1 > obj2)
        return obj1;
    else
        return obj2;
}

// Die Spezialisierungen für C-Strings
template <>                                           // Spezialisierung
const char* maxi(const char* str1, const char* str2) { // statt T, const char*
    if (strcmp(str1, str2) > 0)
        return str1;
    else
        return str2;
}

int main() {
    int    a = 3;                         // Ganzzahlige Variable
    double b = 5.4;                       // Gleitkommazahl-Variable

    int    m;                             // Ganzzahl-Ergebnis
    double n;                             // Kommazahl-Ergebnis

    // Je nachdem, wo die Typumwandlungen stattfinden, sind die Ergebnisse unterschiedlich
    m = maxi<int>(a, b);                  // m == 5
    n = maxi<int>(a, b);                  // n == 5.0
    m = maxi<double>(a, b);               // m == 5
    n = maxi<double>(a, b);               // n == 5.4

    // Aufgerufen wird unabhänngig vom Ergebnistyp m:
    m = maxi(3, 6);                       // maxi<int>()
    m = maxi(3.0, 6.0);                   // maxi<double>()
    m = maxi<int>(3.0, 6);                // maxi<int>()
    m = maxi<double>(3, 6.0);             // maxi<double>()

    // Aufruf von maxi<std::string>()
    string s1("alpha");
    string s2("omega");
    string smax = maxi(s1, s2);           // smax == omega
    maxi<std::string>("Ich bin ein C-String!", "Ich auch!");  // ie beiden C-Strings werden vor dem Aufruf in C++-Strings umgewandelt

    // Aufruf von maxi<const char*>()
    smax = maxi("alpha", "omega");        // Spezialisierung wird aufgerufen

    return 0;                            // Programm erfolgreich durchlaufen
}


/*  Überladen vs Spezialisierung

#include <iostream>          // Ein und Ausgabe
#include <string>            // C++-Strings
#include <cstring>           // Vergleiche von C-Strings

using namespace std;

// Unsere Standardvorlage für maxi() mit 2 Argumenten
template <typename T>
T maxi(T obj1, T obj2){
  if (obj1 > obj2)
    return obj1;
  else
    return obj2;
}

// Die Spezialisierungen für C-Strings mit zwei Argumenten
template <> // Spezialisierung
const char* maxi(const char* str1, const char* str2){
    if(strcmp(str1, str2) > 0)
        return str1;
    else
        return str2;
}

// Unsere Standardvorlage für maxi() mit drei Argumenten
template <typename T>
T maxi(T obj1, T obj2, T obj3){
    if(obj1 > obj2)
        if(obj1 > obj3)
            return obj1;
        else
            return obj3;
    else if(obj2 > obj3)
        return obj2;
    else
        return obj3;
}

// Die Spezialisierungen für C-Strings mit drei Argumenten
template <> // Spezialisierung
const char* maxi(const char* str1, const char* str2, const char* str3){
    if(strcmp(str1, str2) > 0){
        if(strcmp(str1, str3) > 0)
            return str1;
        else
            return str3;
    }
    else if(strcmp(str2, str3) > 0)
        return str2;
    else
        return str3;
}

int main(){
    cout << "Beispiele für Ganzzahlen:\n";
    cout << "      (2, 7, 4) -> " << maxi(2, 7, 4) << endl;
    cout << "         (2, 7) -> " << maxi(2, 7)    << endl;
    cout << "         (7, 4) -> " << maxi(7, 4)    << endl;

    cout << "\nBeispiele für Kommazahlen:\n";
    cout << "(5.7, 3.3, 8.1) -> " << maxi(5.7, 3.3, 8.1) << endl;
    cout << "     (7.7, 7.6) -> " << maxi(7.7, 7.6)      << endl;
    cout << "     (1.9, 0.4) -> " << maxi(1.9, 0.4)      << endl;

    cout << "\nBeispiele für C-Strings:\n";
    cout << "(ghi, abc, def) -> " << maxi("ghi", "abc", "def") << endl;
    cout << "     (ABC, abc) -> " << maxi("ABC", "abc")        << endl;
    cout << "     (def, abc) -> " << maxi("def", "abc")        << endl;

    return 0;                            // Programm erfolgreich durchlaufen
}
 
 
*/