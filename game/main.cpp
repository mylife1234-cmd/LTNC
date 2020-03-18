#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>
#include<cmath>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;

const int Number_of_plays = 8;
const string FIGURE[] = {
    "   -------------    \n"
         "   |                \n"
         "   |                \n"
         "   |                \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",
         "   -------------    \n"
         "   |           |    \n"
         "   |                \n"
         "   |                \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",
          "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |                \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",
          "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |           |    \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",
          "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |          /|    \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",
          "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |          /|\\  \n"
         "   |                \n"
         "   |     \n"
         " -----   \n",
          "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |          /|\\  \n"
         "   |          /     \n"
         "   |     \n"
         " -----   \n",
          "   -------------    \n"
         "   |           |    \n"
         "   |           O    \n"
         "   |          /|\\  \n"
         "   |          / \\  \n"
         "   |     \n"
         " -----   \n"
};
void BackGround(string guessWord, int yourWrongAnswer)
{
    system("CLS");   // lenh xoa man hinh
    cout << FIGURE[yourWrongAnswer] << endl;
    cout << guessWord << endl;
    cout << "Number of wrong guesses : " << yourWrongAnswer << endl;
}
string toLowerCase1(const string &s)
{
    string res=s;
    transform(s.begin(), s.end(), res.begin(), :: tolower);
    return res;
}
string toLowerCase(const string &s)
{
    string res=s;
    int n=s.size();
    for(int i=0;i<n; i++ )
    {
        res[i]=tolower(s[i]);
        return res;
    }
}
string chooseWord(int level)
{
    const char*filename;
    vector<string> wordlist;
    if(level==1) filename="C:\\Users\\vuman\\OneDrive\\Máy tính\\code\\C++\\input1.txt";
    if(level==2) filename="C:\\Users\\vuman\\OneDrive\\Máy tính\\code\\C++\\input2.txt";
    if(level==3) filename="C:\\Users\\vuman\\OneDrive\\Máy tính\\code\\C++\\input3.txt";
    if(level==4) filename="C:\\Users\\vuman\\OneDrive\\Máy tính\\code\\C++\\input4.txt";
    ifstream file(filename);
    if(file.is_open())
    {
        string word;
        while(file>>word)
        {
            wordlist.push_back(word);
        }
        file.close();
    }
    if(wordlist.size()>0)
    {
        int randomIndex=rand() % wordlist.size();
        return toLowerCase1(wordlist[randomIndex]);
    }
    else return "";
}

char InputAGuess()
{
    char ch;
    cout << "Enter the your char :";
    cin >> ch;
    return ch;
}

bool checkGuessChar(string hiddenWord, string question, char guess)
{
    return (hiddenWord.find_first_of(guess) != string::npos? true : false);
}

string update(string hiddenWord, string guessWord, char guess)
{
    int n = hiddenWord.length();
    for(int i=0; i < n; i++)
    {
        if(hiddenWord[i]==guess)
        {
            guessWord[i]=guess;
        }
    }
    cout << guessWord << endl;
    return guessWord;
}

bool checkWord(string guessWord, string hiddenWord){
  if(guessWord == hiddenWord) return true;
  else return false;
}

void play_Hangman(string hiddenWord, int level)
{
    srand(time(0));
    hiddenWord = chooseWord(level);
    if(hiddenWord.length()<1)
    {
        cout << "Error reading file";
        exit(1);
    }
    string guessWord = string (hiddenWord.length(),'_');
    int yourWrongAnswer =0;
    char guess;
    while(guessWord!=hiddenWord){
        BackGround(guessWord,yourWrongAnswer);
        guess = InputAGuess();
        bool check = checkGuessChar(hiddenWord,guessWord,guess);
        if(check == true)
        {
            guessWord = update(hiddenWord,guessWord,guess);
            if(checkWord(guessWord, hiddenWord) == true ){
                cout << "You Won !\n";
                break;
            }
        }
        else{
            yourWrongAnswer++;
            if(yourWrongAnswer==Number_of_plays)
            {
                cout << "You lost !" << endl;
                break;
            }
        }
    }
}
int main()
{
    string hiddenWord;
    int level;
    bool check;
    char ch;
    cout << "WELCOME TO THE GAME: 'HANGMAN' ! \n"
         << "The Rule of Game:\n"
         << "Each play will have" << Number_of_plays <<  "plays.\n"
         << "Your task is to guess the correct word of mysteries.\n"
         << "If you answer more than" <<  Number_of_plays  << "times, you will lose.\n"
         << "Are you ready ?\n"
         << "Now ! Let's start !\n";
    do{
        cout << "Choose the level of game:\n"
             << "1. Easy level\n"
             << "2. Medium level\n"
             << "3. Hard level\n"
             << "4. Very Hard Level\n\n"
             << "Your choice is:";
        cin >> level;
        switch(level)
        {
            case 1:
                cout << "You choose : Easy Level\n";
                break;
            case 2:
                cout << "You choose : Medium Level\n";
                break;
            case 3:
                cout << "You choose : Hard Level\n";
                break;
            case 4:
                cout << "You choose : Very Hard Level\n";
                break;
        }
        play_Hangman(hiddenWord,level);
        cout << "Do you want to  play again ? (y/n):" ;
        cin >> ch;
        if(ch=='y'){
            check=true;
        }
        if(ch=='n'){
            check=false;
        }
    }while(check==true);
    return 0;
}
