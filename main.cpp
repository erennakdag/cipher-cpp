#include <iostream>
#include <fstream>
#include <string>

using std::string;

// prototypes
string cipher(string,int);
string decipher(string);
void displayCorrectUsage();

int main(int argc, char **argv) {
    // checking if the correct amount of arguments was given
    if (argc < 3) {
        displayCorrectUsage();
        return -1;
    }

    // c_str -> std::string
    string flag(argv[1]);
    string filename(argv[2]);

    string text = "";
    bool fileExists = false;
    if (filename.find(".txt") != -1) {
        std::ifstream infile;
        fileExists = true;
        infile.open(filename);
        string buffer;
        while (std::getline(infile, buffer)) {
            text += buffer + "\n";
        }
        infile.close();
    } else {
        text = filename;
    }

    string outputText;
    // ciphering
    if (flag.compare("-c") == 0) {
        // key is absent
        if (argc != 4) {
            std::cout << "You must enter a key!" << std::endl;
            displayCorrectUsage();
            return -1;
        }
        outputText = cipher(text, std::stoi(argv[3]));
    }
    // deciphering
    else if (flag.compare("-d") == 0) {
        outputText = decipher(text);
    }
    // wrong flag
    else {
        std::cout << "Wrong flag!\n";
        displayCorrectUsage();
        return -1;
    }

    if (fileExists) {
        std::ofstream outfile(filename, std::ios::app);
        if (!outfile.is_open()) {
            std::cerr << "Could not open file to write!" << std::endl;
            return -1;
        }
        outfile << outputText;
        outfile.close();
    } else {
        std::cout << outputText;
    }
    return 0;
}

string cipher(string text, int key) {
    // if key is bigger than the size of the alphabet
    key %= 26;

    string res = "";
    for (int i = 0; i < text.length(); i++) {

        int char_ascii = int(text[i]);
        // given char is a letter (upper or lower)
        if ((char_ascii > 64 && char_ascii < 91) || (char_ascii > 96 && char_ascii < 123)) {
            int withKey = char_ascii + key;
            // if char goes over the limit (z) -> -26 to bring it within the alphabet
            res += char((withKey > 122) || (withKey > 90 && char_ascii < 91) ? (withKey - 26) : withKey);
        }
        // char not a letter, take it as it is
        else {
            res += text[i];
        }
    }
    return res;
}

string decipher(string cipheredText) {
    // print out all ciphers for all the keys
    string res = "";
    for (int key = 0; key < 26; key++) {
        res += cipher(cipheredText, key) + '\n';
    }
    return res;
}

void displayCorrectUsage() {
    std::cout << "Usage:\n ./main -c \"Your text here\" key\nor\n ./main -d \"Your text to decipher here\"" << std::endl;    
}
