#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <dirent.h>
#include <unistd.h>
#include <cstdlib>
    using namespace std;

//***Functions.
void logInVerification();
void mainMenu();
void createNewTxtFile();
void displayTxtFiles();
void deleteTxtFile();

//***Classes.
class User{
    public: 
        string name;
        int age;
};

void printLog(){
    fstream userFile("logFile.txt");

    //Verify if file exists.
    if(!userFile.is_open()){
    cout << "Error!!! File cannot be opened.\nExiting Program!" << endl;
    exit(0);
    }
    for(string line; getline(userFile, line);){
        cout << line << endl;
    }
    userFile.close();
}

//***Main.
int main(){
    logInVerification();
    mainMenu();
    return 0;
}

//Log in verification.
void logInVerification(){
    cout << endl << "Welcome to your Daily Planner" << endl;

    int i = 0;
    string returningUsername, returningPassword;
    string newUsername, newPassword;

    while(i == 0){
        cout << endl << "Choose an Option\n1.Log in(Returning User)\n2.Sign up(New User)\n3.Quit" << endl;

        int selection;
        cout << "Selection: ";
        cin >> selection;

        //Quit.
        if(selection == 3){
            cout << endl << "Good Bye!" << endl;
            exit(0);
        }

        //Log in.
        if(selection == 1){
            cout << endl << "Welcome Back!\nPlease enter username and password" << endl;

            //Get Username.
            cout << "Username: ";
            cin >> returningUsername;

            //Get Password.
            cout << "Password: ";
            cin >> returningPassword;

            //Open File.
            ifstream userFile("logFile.txt", ios::out);

            //Verify if file exists.
            if(!userFile.is_open()){
            cout << "Error!!! File cannot be opened.\nExiting Program!" << endl;
            exit(0);
            }

            //Read line1 and line2 from text file.
            string line1, line2;
            getline(userFile, line1);
            getline(userFile, line2);

            //Checks if username and password are correct.
            if(line1 == returningUsername && line2 == returningPassword){
                cout << endl << "Logging in...\nAccess granted!\nWelcome Back!" << endl;
                i++;
            }

            else{
                cout << endl << "Incorrect username or Password!" << endl;
            }
        }

        //Sign up.
        if(selection == 2){
            cout << "Welcome, new user!" << endl;

            //Assigns pointer.
            User user1;
            User* userPtr = &user1;

            cout << "Please enter your name!\nName: ";
            cin >> userPtr->name;

            cout << "Please enter your age\nAge: ";
            cin >> userPtr->age;

            cout << endl << "Please enter a username and password." << endl;
            cout << "Important: Creating a new username and password will delete previous account!" << endl;

            //Get Username.
            cout << endl << "Username: ";
            cin >> newUsername;

            //Get Password.
            cout << endl << "Password: ";
            cin >> newPassword;

            //Verify input.
            cout << "Verify your username and password by entering them again" << endl;
            string verifyUsername, verifyPassword;

            //Get Username.
            cout << endl << "Username: ";
            cin >> verifyUsername;

            //Get Password.
            cout << endl << "Password: ";
            cin >> verifyPassword;

            //Verify if username and passwords are correct.
            if(newUsername == verifyUsername && newPassword == verifyPassword){
                cout << endl << "Success! Welcome in.\n" << endl;

                //Adds username and password to text file.
                ofstream userFile("logfile.txt", ios::trunc);

                //Verify if file exists.
                if(!userFile.is_open()){
                cout << "Error!!! File cannot be opened.\nExiting Program!" << endl;
                return;
                }

                //Write to file.
                userFile << newUsername;
                userFile << endl;
                userFile << newPassword;
                userFile << endl;
                userFile << userPtr->name;
                userFile << endl;
                userFile << userPtr->age;
                userFile << endl;
                userFile.close();

                cout << "Username and Password Created!\nPlease Log in now by pressing 1!\n"  << endl;
            }
            else{
                cout << endl << "Error! Try Again...\n" << endl;
            }
        }
    }
}

//Display Main Menu.
void mainMenu(){
    int selection, i = 0;
    while(i == 0){ 
        cout << endl << "Main Menu" << endl;
        cout << "1.Show Files\n2.Create New File\n3.Delete File\n4.Show Log File\n5.Exit Program\nSelection: ";
        cin >> selection;

        if(selection == 1){
            cout << endl << "Show Files" << endl;
            displayTxtFiles();
        }

        if(selection == 2){
            cout << endl << "Create New File" << endl;
            createNewTxtFile();
            cout << "Your text file has been created!" << endl;
        }

        if(selection == 3){
            cout << endl << "Choose File to Delete" << endl;
            displayTxtFiles();
            deleteTxtFile();
        }

        if(selection == 4){
            cout << endl << "Log File\n--------" << endl;
            printLog();
        }

        if(selection == 5){
            cout << "Good Bye!" << endl;
            exit(0);
        }

        if(selection < 1 || selection > 5){
            cout << endl << "Choice has to be between 1 - 4" << endl;
        }
        else{
            cout << endl << "Choose an option" << endl;
        }
    }
}

//Create new .txt file.
void createNewTxtFile(){
    string nameOfFile, convertTxt = ".txt";
    cout << endl << "Please enter name of file\nFile name: ";
    cin >> nameOfFile;

    //Adds ".txt" at the end of input.
    nameOfFile.append(convertTxt);

    ofstream newPlannerFile(nameOfFile, ios::app);
        
    //Verify if file exists.
    if(!newPlannerFile.is_open()){
        cout << "Error!!! File cannot be opened.\nExiting Program!" << endl;
        return;
    }
    cout << "Your file name is " << nameOfFile << endl;
    newPlannerFile.close();
}

void displayTxtFiles(){
    //Open the current directory.
    DIR* dir = opendir(".");

    if(dir != nullptr){
        cout << "Text files in the current folder:" << endl;

        //Read directory entries.
        struct dirent* entry;
        bool foundTxtFile = false;
        while((entry = readdir(dir)) != nullptr){
            //Check if the file has a .txt extension.
            if(strstr(entry->d_name, ".txt") != nullptr){

                //Exclude logfile.
                if(strcmp(entry->d_name, "logfile.txt") != 0){
                    cout << entry->d_name << endl;
                }
            }
        }

        //Close the directory.
        closedir(dir);
    } 
    else{
        cout << "Error opening directory." << std::endl;
        return;
    }
}

void deleteTxtFile() {
    string userInput;
    cout << endl << "Enter name of file to delete or type 'exit' to go back to main menu\nFile name: ";
    cin >> userInput;

    //Choice to exit.
    if(userInput == "exit"){
        cout << "Exiting..." << endl;
        return;
    } 
    else{
        //Delete file.
        if(unlink(userInput.c_str()) == 0){
            cout << "File deleted successfully." << endl;
        }
        else{
            cout << "Error deleting the file." << endl;
        }
    }
}
