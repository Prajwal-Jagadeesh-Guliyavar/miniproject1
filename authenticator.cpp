#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Base class for handling file operations
class FileHandler {
protected:
    string filepath;
public:
    FileHandler(const string& path) : filepath(path) {}

    void appendToFile(const string& line) {
        ofstream file(filepath, ios::app);
        if (file.is_open()) {
            file << line << endl;
            file.close();
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    }

    ifstream openFileForReading() {
        ifstream file(filepath);
        if (!file.is_open()) {
            cout << "Unable to open file for reading." << endl;
        }
        return file;
    }
};

// Derived class for user authentication
class UserAuthenticator : public FileHandler {
public:
    UserAuthenticator(const string& path) : FileHandler(path) {}

    bool verify_loginid(const string& username, const string& password) {
        int count = 0;
        string line;
        try {
            ifstream file = openFileForReading();
            if (file.is_open()) {
                while (getline(file, line)) {
                    stringstream ss(line);
                    string user, pass;
                    if (getline(ss, user, ',') && getline(ss, pass)) {
                        if (username == user) {
                            count++;
                            if (password == pass) {
                                cout << "User authentication successful" << endl;
                                return true;
                            }
                        }
                    }
                }
                file.close();
            }

            if (count == 0) {
                cout << "The username is not registered." << endl;
                for (int i = 0; i < 3; i++) {
                    string new_password, confirm_password;
                    cout << "Create a password: ";
                    cin >> new_password;
                    cout << "Re-enter your password: ";
                    cin >> confirm_password;
                    if (new_password == confirm_password) {
                        appendToFile(username + "," + new_password);
                        cout << "Please remember your password\nUser verified" << endl;
                        return true;
                    } else {
                        cout << "The re-entered password is incorrect." << endl;
                    }
                }
            }
        } catch (const exception& e) {
            cout << "An error occurred: " << e.what() << endl;
        } 
        return false;
    }
}; 

int main() {
    string user_name, password;
    cout << "Enter the login ID: ";
    cin >> user_name;
    cout << "Enter the password: ";
    cin >> password;
    UserAuthenticator auth("login_info.txt");
    auth.verify_loginid(user_name, password);
    return 0;
}
