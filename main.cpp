#include <iostream>
#include <ctime>
#include <cstdlib>
#include <winbase.h>

using namespace std;

//zmiana rozmiaru planszy
//w przypadku gry z komputerem proszę zostawić 3
#define N 3


/*
 * Do poniższego zadania (gra w kółko i krzyżyk) dodać następujące możliwości:
 *\\\\\\\\\    1. Wybór znaków do grania (zamiast kółka i krzyżyka -- proszę pamiętać, że nie mogą to być dwa identyczne znaki.
 *\\\\\\\\\    2. Zmienna wielkość planszy (wielkość planszy podawana przed kompilacją, w formie stałej globalnej, a więc: const N=wielkość).
 *\\\\\\\\\    3. Gra jednego użytkownika z komputerem (przynajmniej dla ustalonej planszy 3x3).
 *    4. Dodanie poziomów do gry komputera (1. łatwy (losowy), 2. średni (w pewnym procencie losowy), 3. trudny (optymalny)).
 *    5. Dodać możliwość cofnięcia ruchu.
 */


void copyMatrix(char tab[N][N], char copy[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            copy[i][j] = tab[i][j];
        }
    }
}

void tabela(char t[N][N]) {
    cout << "   ";
    for (int a = 0; a < N; a++) cout << "_ _ ";
    char temp = 97;
    cout << endl;
    cout << " ";
    for (int a = 0; a < N; a++) {
        cout << " | " << (char) (temp + a);
    }

    cout << " |" << endl;
    for (int i = 0; i < N; i++) {
        cout << i + 1 << " |";
        for (int j = 0; j < N; j++) {
            cout << " " << t[i][j] << " |";
        }
        cout << endl;
    }

    cout << "   ";
    for (int a = 0; a < N; a++) cout << "‾ ‾ ";
    cout << endl;
}

bool pobierz(char t[N][N], int &kto, char character1, char character2, int difficultyLevel, int withWho) {
    char poz[N];

    cout << endl;
    char sizeLetter = 97;
    char sizeNumber = 48;
    if(withWho == 1){
        if(!(kto%2))
            cout<< "Gracz 1-szy, ";
        else
            cout<< "Gracz 2-gi,  ";
        do{
            cout<<"podaj pozycję, którą zaznaczyć (np. a1): "<<endl;
            cin>>poz;
        }while((poz[0]<'a' || poz[0]>(sizeLetter + N-1)) || (poz[1]<'1' || poz[1]>(sizeNumber + N)));
    }
    else if(withWho == 2){
        if (!(kto % 2)) {
            cout << "Gracz 1, ";
            do {
                cout << "podaj pozycję, którą zaznaczyć (np. a1): " << endl;
                cin >> poz;

            } while ((poz[0] < 'a' || poz[0] > 'c') || (poz[1] < '1' || poz[1] > '3'));
        } else {
            cout << "Gracz 2: myśli..." << endl;
            //Sleep(1500);
            //POZIOM ŁATWY
            //pełna losowość
            if (difficultyLevel == 1) {
                do {
                    srand(time(NULL));
                    char randNum = (rand() % (52 - 49)) + 49;
                    char randLetter = (rand() % (100 - 97)) + 97;
                    poz[0] = randLetter;
                    poz[1] = randNum;
                } while (t[poz[1] - '1'][poz[0] - 'a'] != ' ');
            }
                //POZIOM ŚREDNI
                //na poziomie średnim komputer blokuje nam środek planszy w przypadku zaznaczenia przez gracza pola na rogu planszy oraz blokuje 2 z 4 dostępnych możliwości na przekątnych
                //(gdy gracz uzupełni pole a1 oraz b2 komputer zablokuje c3) oraz (gdy gracz uzupełni pole c1 oraz b2 komputer zablokuje a3)
            else if(difficultyLevel == 2){
                do {
                    if((t[0][0] != ' ' || t[0][2] != ' ' || t[2][0] != ' ' || t[2][2] != ' ') && t[1][1] == ' '){
                        poz[0] = 'b';
                        poz[1] = '2';
                    }
                    else if((t[0][0] == character1 && t[1][1] == character1) && t[2][2] == ' '){
                        poz[0] = 'c';
                        poz[1] = '3';
                    }
                    else if((t[0][2] == character1 && t[1][1] == character1) && t[2][2] == ' '){
                        poz[0] = 'a';
                        poz[1] = '3';
                    }
                    else{
                        srand(time(NULL));
                        char randNum = (rand() % (52 - 49)) + 49;
                        char randLetter = (rand() % (100 - 97)) + 97;
                        poz[0] = randLetter;
                        poz[1] = randNum;
                    }
                } while (t[poz[1] - '1'][poz[0] - 'a'] != ' ');
            }
                //POZIOM TRUDNY
                // w poziomie trudnym komputer blokuje nasze ruchy na wszystkich przekątnych oraz większości trójek wertykalnie jak i horyzontalnie
            else{
                do {
                    if((t[0][0] != ' ' || t[0][2] != ' ' || t[2][0] != ' ' || t[2][2] != ' ') && t[1][1] == ' '){
                        poz[0] = 'b';
                        poz[1] = '2';
                    }
                    else if((t[0][0] == character1 && t[1][1] == character1) && t[2][2] == ' '){
                        poz[0] = 'c';
                        poz[1] = '3';
                    }
                    else if((t[0][2] == character1 && t[1][1] == character1) && t[2][0] == ' '){
                        poz[0] = 'a';
                        poz[1] = '3';
                    }
                    else if((t[2][2] == character1 && t[1][1] == character1) && t[0][0] == ' '){
                        poz[0] = 'a';
                        poz[0] = '1';
                    }
                    else if((t[2][0] == character1 && t[1][1] == character1) && t[0][2] == ' '){
                        poz[0] = 'c';
                        poz[1] = '1';
                    }
                    else if((t[0][0] == character1 && t[1][0] == character1) && t[2][0] == ' '){
                        poz[0] = 'a';
                        poz[1] = '3';
                    }
                    else if((t[0][0] == character1 && t[0][2] == character1) && t[0][1] == ' '){
                        poz[0] = 'b';
                        poz[1] = '1';
                    }
                    else if((t[0][2] == character1 && t[2][2] == character1) && t[1][2] == ' '){
                        poz[0] = 'c';
                        poz[1] = '2';
                    }
                    else if((t[0][1] == character1 && t[2][1] == character1) && t[1][1] == ' '){
                        poz[0] = 'b';
                        poz[1] = '2';
                    }
                    else if((t[0][2] == character1 && t[1][2] == character1) && t[2][2] == ' '){
                        poz[0] = 'c';
                        poz[1] = '3';
                    }
                    else if((t[0][1] == character1 && t[0][2] == character1) && t[0][0] == ' '){
                        poz[0] = 'a';
                        poz[1] = '1';
                    }
                    else if((t[1][1] == character1 && t[1][2] == character1) && t[1][0] == ' '){
                        poz[0] = 'a';
                        poz[1] = '2';
                    }
                    else if((t[1][1] == character1 && t[2][1] == character1) && t[0][1] == ' '){
                        poz[0] = 'b';
                        poz[1] = '1';
                    }
                    else if((t[1][0] == character1 && t[1][2] == character1) && t[1][1] == ' '){
                        poz[0] = 'b';
                        poz[1] = '2';
                    }
                    else if((t[0][0] == character1 && t[2][0] == character1) && t[1][0] == ' '){
                        poz[0] = 'a';
                        poz[1] = '2';
                    }
                    else if((t[0][0] == character1 && t[0][1] == character1) && t[0][2] == ' '){
                        poz[0] = 'c';
                        poz[1] = '1';
                    }

                    else if(t[1][1] == character1 && (t[0][0] == ' ' || t[0][2] == ' ' || t[2][0] == ' ' || t[2][2] == ' ')) {
                        srand(time(NULL));
                        char randNum = (rand() % (52 - 49)) + 49;
                        char randLetter = (rand() % (100 - 97)) + 97;
                        poz[0] = randLetter;
                        poz[1] = randNum;
                    }
                    else{
                        srand(time(NULL));
                        char randNum = (rand() % (52 - 49)) + 49;
                        char randLetter = (rand() % (100 - 97)) + 97;
                        poz[0] = randLetter;
                        poz[1] = randNum;
                    }
                } while (t[poz[1] - '1'][poz[0] - 'a'] != ' ');
            }
        }
    }


    if (t[poz[1] - '1'][poz[0] - 'a'] != ' ') {
        cout << endl << "Pole " << poz << " było już uzupełnione." << endl;
        return pobierz(t, kto, character1, character2, difficultyLevel, withWho);
    }

    if (!(kto++ % 2))
        t[poz[1] - '1'][poz[0] - 'a'] = character1;
    else
        t[poz[1] - '1'][poz[0] - 'a'] = character2;

    return true;
}

bool rozwiazanie(char t[N][N]) {
    int bz = 0;
    bool x, y;
    bool p1 = true, p2 = true;
    for (int i = 0; i < 3; i++) {
        x = true;
        y = true;
        for (int j = 1; j < N; j++) {
            if (t[i][j] != t[i][j - 1])
                x = false;
            if (t[j][i] != t[j - 1][i])
                y = false;
            if (t[i][j] == ' ') {
                bz++;
                x = false;
            }
            if (t[j][i] == ' ')
                y = false;
        }
        if (x) {
            cout << endl << "Wygrywa: " << t[i][0] << endl << endl;
            return true;
        }
        if (y) {
            cout << endl << "Wygrywa: " << t[0][i] << endl << endl;
            return true;
        }
        if (i < N - 1) {
            if (t[i][i] != t[i + 1][i + 1] || t[i][i] == ' ')
                p1 = false;
            if (t[i][N - 1 - i] != t[i + 1][1 - i] || t[i][N - 1 - i] == ' ')
                p2 = false;
        }

    }

    if (p1) {
        cout << endl << "Wygrywa: " << t[0][0] << endl;
        return true;
    }
    if (p2) {
        cout << endl << "Wygrywa: " << t[0][N-1] << endl;
        return true;
    }

    for (int i = 0; i < N; i++)
        if (t[i][0] == ' ')
            bz++;

    if (bz == 0) {
        cout << endl << "Remis. Plansza jest już pełna." << endl;
        return true;
    }
    return false;
}

int main() {
    char tab[N][N];
    char character1, character2;
    char copy[N][N];
    string choice;
    for (int i = 0; i < N; i++) for (int j = 0; j < N; tab[i][j++] = ' ');
    int kto = 0, difficultyLevel = 0, withWho = 0;
    bool koniec = false;


    cout << "(1) - Gracz vs Gracz" << endl << "(2) - Gracz vs komputer" << endl;
    do{
        cout << "Wybierz tryb rozgrywki:";
        cin >> withWho;
    } while (withWho < 1 || withWho > 2);



    if(withWho == 1){
        cout << "Podaj pierwszy znak wypełniania: ";
        cin >> character1;
        do {
            cout << "Podaj drugi znak wypełniania: ";
            cin >> character2;
        } while (character1 == character2);
        while (!koniec) {
            tabela(tab);
            copyMatrix(tab, copy);
            pobierz(tab, kto, character1, character2, difficultyLevel, withWho);
            cout << "Na pewno? Wpisz 'nie' aby cofnąć swój ruch: ";
            cin >> choice;
            if(choice == "nie" || choice == "n"){
                copyMatrix(copy,tab);
            }
            else{
                kto++;
            }
            kto++;
            koniec = rozwiazanie(tab);
        }
        tabela(tab);
    }
    else if(withWho == 2){
        cout << "Wybierz poziom trudności: (1 - łatwy, 2 - średni, 3 - trudny)";
        do {
            cin >> difficultyLevel;
        } while (difficultyLevel < 1 || difficultyLevel > 3);
        cout << "Podaj pierwszy znak wypełniania: ";
        cin >> character1;
        do {
            cout << "Podaj drugi znak wypełniania: ";
            cin >> character2;
        } while (character1 == character2);
        while (!koniec) {
            tabela(tab);
            pobierz(tab, kto, character1, character2, difficultyLevel, withWho);
            koniec = rozwiazanie(tab);
        }
        tabela(tab);
    }



    return 0;
}
