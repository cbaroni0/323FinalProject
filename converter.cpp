#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    ifstream inFile("final.txt");
    ofstream outFile("aba13.txt");
    
    string line;
    string word;
    string array[50];
    int i = 0;
    
    if (inFile.is_open())
    {
        while (getline(inFile, word))
        {
            array[i] = word;
            i++;
        }
    
    }
    inFile.close();
    
    int length = sizeof(array) / sizeof(array[0]);
    
    for (i = 0; i < length; i++)
    {
        if (array[i].find("PROGRAM") != string::npos)
        {
            outFile << "#include <iostream>\n"
                    << "using namespace std;\n"
                    << "int main()\n"
                    << "{\n";
        }
        
        if (array[i] == "INTEGER;")
        {
            outFile << "int ab5, cb, be, eb;\n";
        }
        
        if (array[i] == "BEGIN")
            outFile << "ab5 = 5;\n"
                    << "cb = 10;\n";

        if (array[i] == "PRINT('ab5='," )
        {
            outFile << "cout << â€ab5=â€ << "
                    << "ab5;\n"
                    << "eb = cb + ab5;\n";
        }

        if ( array[i] == "PRINT(")
        {
            outFile << "cout << eb;\n"
                    << "be = 2 * ab5 + eb;\n";
        }
        
        if ( array[i] == "PRINT( ")
            cout << "cout << be\n";

        if ( array[i] == "END.")
        {
            outFile << "return 0;\n}";
        }
            
    }
    
    for (int j = 0; j < length; j++)
    {
        cout << j << array[j] << endl;
    }
    return 0;
}
