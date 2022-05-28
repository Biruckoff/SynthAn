// Otyp.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <vector>
#include<cstring> 


using namespace std;

// Состояния автомата
enum states { S, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Fall, Space, Begin, Y,X,Z };
enum signals { letter, digit, plus_minus, more, less_, equals, space, fall };
// Типы лексем (ключевое слово, оператор сравнения, арифметический оператор, идентификатор, константа)
enum statesSynth { s_S, s_A, s_B, s_C, s_D, s_E, s_F, s_G, s_H, s_I, s_J, s_K, s_L, s_M, s_End,s_Err };
enum ELexType { kw, vl, ao, id, wl, co, sp, eq,de,ca,en,se };

// Вектор лексем
struct Lex
{
    ELexType type;
    int amount_free;
    char* word;
    Lex* next;
    Lex(int n)
    {
        next = 0;
        amount_free = n;
        word = new char[amount_free + 1];
        word[amount_free] = '\0';
    }
    Lex() {
        next = 0;

    }
    //Функция записи слова в структуру лексемы
    void set_word(char* m)
    {
        int k = 0;

        while (k < amount_free) {
            word[k] = m[k];
            k++;
        }


    }
    ~Lex() {
        delete[] word;
        if (next) {
            delete next;
        }
    }
};
//Таблица для ElexType
void table_creation(char(*table)[2])
{
    table[0][0] = 'k';
    table[0][1] = 'w';

    table[1][0] = 'v';
    table[1][1] = 'l';

    table[2][0] = 'a';
    table[2][1] = 'o';

    table[3][0] = 'i';
    table[3][1] = 'd';

    table[4][0] = 'w';
    table[4][1] = 'l';

    table[5][0] = 'c';
    table[5][1] = 'o';

    table[6][0] = 's';
    table[6][1] = 'p';

    table[7][0] = 'e';
    table[7][1] = 'q';

    table[8][0] = 'd';
    table[8][1] = 'e';

    table[9][0] = 'c';
    table[9][1] = 'a';

    table[10][0] = 'e';
    table[10][1] = 'n';

    table[11][0] = 's';
    table[11][1] = 'e';

}

void table_creation(states(*table)[8])
{
    table[S][letter] = A;
    table[S][digit] = F;
    table[S][plus_minus] = K;
    table[S][more] = N;
    table[S][less_] = L;
    table[S][equals] = P;
    table[S][space] = Space;
    table[S][fall] = Fall;


    table[Begin][letter] = A;
    table[Begin][digit] = F;
    table[Begin][plus_minus] = K;
    table[Begin][more] = N;
    table[Begin][less_] = L;
    table[Begin][equals] = P;
    table[Begin][space] = S;
    table[Begin][fall] = Fall;

    table[Space][letter] = S;
    table[Space][digit] = S;
    table[Space][plus_minus] = S;
    table[Space][more] = S;
    table[Space][less_] = S;
    table[Space][equals] = S;
    table[Space][space] = S;
    table[Space][fall] = Fall;

    table[A][letter] = B;
    table[A][digit] = B;
    table[A][plus_minus] = S;
    table[A][more] = S;
    table[A][less_] = S;
    table[A][equals] = S;
    table[A][space] = S;
    table[A][fall] = Fall;

    table[B][letter] = C;
    table[B][digit] = C;
    table[B][plus_minus] = S;
    table[B][more] = S;
    table[B][less_] = S;
    table[B][equals] = S;
    table[B][space] = S;
    table[B][fall] = Fall;

    table[C][letter] = D;
    table[C][digit] = D;
    table[C][plus_minus] = S;
    table[C][more] = S;
    table[C][less_] = S;
    table[C][equals] = S;
    table[C][space] = S;
    table[C][fall] = Fall;

    table[D][letter] = E;
    table[D][digit] = E;
    table[D][plus_minus] = S;
    table[D][more] = S;
    table[D][less_] = S;
    table[D][equals] = S;
    table[D][space] = S;
    table[D][fall] = Fall;

    table[E][letter] = Y;
    table[E][digit] = Fall;
    table[E][plus_minus] = S;
    table[E][more] = S;
    table[E][less_] = S;
    table[E][equals] = S;
    table[E][space] = S;
    table[E][fall] = Fall;

    table[Y][letter] = X;
    table[Y][digit] = Fall;
    table[Y][plus_minus] = S;
    table[Y][more] = S;
    table[Y][less_] = S;
    table[Y][equals] = S;
    table[Y][space] = S;
    table[Y][fall] = Fall;

    table[X][letter] = Fall;
    table[X][digit] = Fall;
    table[X][plus_minus] = S;
    table[X][more] = S;
    table[X][less_] = S;
    table[X][equals] = S;
    table[X][space] = S;
    table[X][fall] = Fall;

    table[F][letter] = Fall;
    table[F][digit] = G;
    table[F][plus_minus] = S;
    table[F][more] = S;
    table[F][less_] = S;
    table[F][equals] = S;
    table[F][space] = S;
    table[F][fall] = Fall;

    table[G][letter] = Fall;
    table[G][digit] = H;
    table[G][plus_minus] = S;
    table[G][more] = S;
    table[G][less_] = S;
    table[G][equals] = S;
    table[G][space] = S;
    table[G][fall] = Fall;

    table[H][letter] = Fall;
    table[H][digit] = I;
    table[H][plus_minus] = S;
    table[H][more] = S;
    table[H][less_] = S;
    table[H][equals] = S;
    table[H][space] = S;
    table[H][fall] = Fall;

    table[I][letter] = Fall;
    table[I][digit] = J;
    table[I][plus_minus] = S;
    table[I][more] = S;
    table[I][less_] = S;
    table[I][equals] = S;
    table[I][space] = S;
    table[I][fall] = Fall;

    table[J][letter] = Fall;
    table[J][digit] = Fall;
    table[J][plus_minus] = S;
    table[J][more] = S;
    table[J][less_] = S;
    table[J][equals] = S;
    table[J][space] = S;
    table[J][fall] = Fall;

    table[K][letter] = S;
    table[K][digit] = S;
    table[K][plus_minus] = S;
    table[K][more] = S;
    table[K][less_] = S;
    table[K][equals] = S;
    table[K][space] = S;
    table[K][fall] = Fall;

    table[L][letter] = S;
    table[L][digit] = S;
    table[L][plus_minus] = S;
    table[L][more] = M;
    table[L][less_] = S;
    table[L][equals] = M;
    table[L][space] = S;
    table[L][fall] = Fall;

    table[M][letter] = S;
    table[M][digit] = S;
    table[M][plus_minus] = S;
    table[M][more] = S;
    table[M][less_] = S;
    table[M][equals] = S;
    table[M][space] = S;
    table[M][fall] = Fall;

    table[N][letter] = S;
    table[N][digit] = S;
    table[N][plus_minus] = S;
    table[N][more] = S;
    table[N][less_] = S;
    table[N][equals] = O;
    table[N][space] = S;
    table[N][fall] = Fall;

    table[O][letter] = S;
    table[O][digit] = S;
    table[O][plus_minus] = S;
    table[O][more] = S;
    table[O][less_] = S;
    table[O][equals] = S;
    table[O][space] = S;
    table[O][fall] = Fall;

    table[P][letter] = S;
    table[P][digit] = S;
    table[P][plus_minus] = S;
    table[P][more] = S;
    table[P][less_] = S;
    table[P][equals] = S;
    table[P][space] = S;
    table[P][fall] = Fall;

    table[Fall][letter] = Fall;
    table[Fall][digit] = Fall;
    table[Fall][plus_minus] = Fall;
    table[Fall][more] = Fall;
    table[Fall][less_] = Fall;
    table[Fall][equals] = Fall;
    table[Fall][space] = S;
    table[Fall][fall] = Fall;
}

void table_creation(statesSynth(*table)[12])
{

    table[s_S][ca] = s_Err;
    table[s_S][vl] = s_Err;
    table[s_S][se] = s_A;
    table[s_S][en] = s_Err;
    table[s_S][de] = s_Err;
    table[s_S][eq] = s_Err;
    table[s_S][sp] = s_Err;
    table[s_S][co] = s_Err;
    table[s_S][wl] = s_Err;
    table[s_S][id] = s_Err;
    table[s_S][ao] = s_Err;

    table[s_A][ca] = s_Err;
    table[s_A][vl] = s_B;
    table[s_A][se] = s_Err;
    table[s_A][en] = s_Err;
    table[s_A][de] = s_Err;
    table[s_A][eq] = s_Err;
    table[s_A][sp] = s_Err;
    table[s_A][co] = s_Err;
    table[s_A][wl] = s_Err;
    table[s_A][id] = s_B;
    table[s_A][ao] = s_Err;

    table[s_B][ca] = s_E;
    table[s_B][vl] = s_Err;
    table[s_B][se] = s_Err;
    table[s_B][en] = s_Err;
    table[s_B][de] = s_Err;
    table[s_B][eq] = s_Err;
    table[s_B][sp] = s_Err;
    table[s_B][co] = s_Err;
    table[s_B][wl] = s_Err;
    table[s_B][id] = s_Err;
    table[s_B][ao] = s_C;

    table[s_C][ca] = s_Err;
    table[s_C][vl] = s_D;
    table[s_C][se] = s_Err;
    table[s_C][en] = s_Err;
    table[s_C][de] = s_Err;
    table[s_C][eq] = s_Err;
    table[s_C][sp] = s_Err;
    table[s_C][co] = s_Err;
    table[s_C][wl] = s_Err;
    table[s_C][id] = s_D;
    table[s_C][ao] = s_Err;

    table[s_D][ca] = s_E;
    table[s_D][vl] = s_Err;
    table[s_D][se] = s_Err;
    table[s_D][en] = s_Err;
    table[s_D][de] = s_Err;
    table[s_D][eq] = s_Err;
    table[s_D][sp] = s_Err;
    table[s_D][co] = s_Err;
    table[s_D][wl] = s_Err;
    table[s_D][id] = s_Err;
    table[s_D][ao] = s_C;

    table[s_E][ca] = s_Err;
    table[s_E][vl] = s_F;
    table[s_E][se] = s_Err;
    table[s_E][en] = s_Err;
    table[s_E][de] = s_Err;
    table[s_E][eq] = s_Err;
    table[s_E][sp] = s_Err;
    table[s_E][co] = s_Err;
    table[s_E][wl] = s_Err;
    table[s_E][id] = s_Err;
    table[s_E][ao] = s_Err;

    table[s_F][ca] = s_Err;
    table[s_F][vl] = s_Err;
    table[s_F][se] = s_Err;
    table[s_F][en] = s_Err;
    table[s_F][de] = s_Err;
    table[s_F][eq] = s_Err;
    table[s_F][sp] = s_Err;
    table[s_F][co] = s_Err;
    table[s_F][wl] = s_Err;
    table[s_F][id] = s_G;
    table[s_F][ao] = s_Err;

    table[s_G][ca] = s_Err;
    table[s_G][vl] = s_Err;
    table[s_G][se] = s_Err;
    table[s_G][en] = s_Err;
    table[s_G][de] = s_Err;
    table[s_G][eq] = s_H;
    table[s_G][sp] = s_Err;
    table[s_G][co] = s_Err;
    table[s_G][wl] = s_Err;
    table[s_G][id] = s_Err;
    table[s_G][ao] = s_Err;

    table[s_H][ca] = s_Err;
    table[s_H][vl] = s_I;
    table[s_H][se] = s_Err;
    table[s_H][en] = s_Err;
    table[s_H][de] = s_Err;
    table[s_H][eq] = s_Err;
    table[s_H][sp] = s_Err;
    table[s_H][co] = s_Err;
    table[s_H][wl] = s_Err;
    table[s_H][id] = s_I;
    table[s_H][ao] = s_Err;

    table[s_I][ca] = s_Err;
    table[s_I][vl] = s_Err;
    table[s_I][se] = s_Err;
    table[s_I][en] = s_End;
    table[s_I][de] = s_Err;
    table[s_I][eq] = s_Err;
    table[s_I][sp] = s_Err;
    table[s_I][co] = s_Err;
    table[s_I][wl] = s_Err;
    table[s_I][id] = s_Err;
    table[s_I][ao] = s_J;

    table[s_J][ca] = s_Err;
    table[s_J][vl] = s_K;
    table[s_J][se] = s_Err;
    table[s_J][en] = s_Err;
    table[s_J][de] = s_Err;
    table[s_J][eq] = s_Err;
    table[s_J][sp] = s_Err;
    table[s_J][co] = s_Err;
    table[s_J][wl] = s_Err;
    table[s_J][id] = s_K;
    table[s_J][ao] = s_Err;

    table[s_K][ca] = s_E;
    table[s_K][vl] = s_Err;
    table[s_K][se] = s_Err;
    table[s_K][en] = s_End;
    table[s_K][de] = s_L;
    table[s_K][eq] = s_Err;
    table[s_K][sp] = s_Err;
    table[s_K][co] = s_Err;
    table[s_K][wl] = s_Err;
    table[s_K][id] = s_Err;
    table[s_K][ao] = s_Err;

    table[s_L][ca] = s_Err;
    table[s_L][vl] = s_M;
    table[s_L][se] = s_Err;
    table[s_L][en] = s_Err;
    table[s_L][de] = s_Err;
    table[s_L][eq] = s_Err;
    table[s_L][sp] = s_Err;
    table[s_L][co] = s_Err;
    table[s_L][wl] = s_Err;
    table[s_L][id] = s_M;
    table[s_L][ao] = s_Err;

    table[s_M][ca] = s_Err;
    table[s_M][vl] = s_Err;
    table[s_M][se] = s_Err;
    table[s_M][en] = s_End;
    table[s_M][de] = s_L;
    table[s_M][eq] = s_Err;
    table[s_M][sp] = s_Err;
    table[s_M][co] = s_Err;
    table[s_M][wl] = s_Err;
    table[s_M][id] = s_Err;
    table[s_M][ao] = s_Err;

    table[s_End][ca] = s_End;
    table[s_End][vl] = s_End;
    table[s_End][se] = s_End;
    table[s_End][en] = s_End;
    table[s_End][de] = s_End;
    table[s_End][eq] = s_End;
    table[s_End][sp] = s_End;
    table[s_End][co] = s_End;
    table[s_End][wl] = s_End;
    table[s_End][id] = s_End;
    table[s_End][ao] = s_End;

}

signals symbol_check(char a)
{
    if (isalpha(a)) return letter;
    if (isdigit(a)) return digit;
    if (a == '+' || a == '-'|| a=='*'||a=='/') return plus_minus;
    if (a == '>') return more;
    if (a == '<') return less_;
    if (a == '=') return equals;
    if (a == ' ' || a == '\n') return space;
    return fall;
}

ELexType getType(states s) {

    if (s == A || s == B || s == C || s == D || s == E || s == Y||s==X) return id;
    if (s == F || s == G || s == H || s == I || s == J) return vl;
    if (s == K) return ao;
    if (s == L || s == M) return  co;
    if (s == N || s == O) return co;
    if (s == P) return eq;
    if (s == Space) return sp;
    return wl;
}


Lex* LexAnalysis(char* text, states(*table)[8])
{
    states current_state = Begin;
    const char* str = text;
    int col = 0;//Количество символов в слове

    Lex* lex = new Lex();
    Lex* head = lex;
    char* word_pos = text; //Начало слова
    while (*str) {


        if (table[current_state][symbol_check(*str)] == S) {
            lex->next = new Lex(col);
            lex->next->set_word(word_pos);
            lex->next->type = getType(current_state);
            lex = lex->next;
            word_pos = word_pos + col;
            col = 0;
            current_state = table[current_state][symbol_check(*str)];

        }
        else {
            current_state = table[current_state][symbol_check(*str)];
            str++;
            col++;
        }

    }
    if (strlen(text) != 0) {
        lex->next = new Lex(col);
        lex->next->set_word(word_pos);
        lex->next->type = getType(current_state);
        lex = lex->next;
        word_pos = word_pos + col;
        col = 0;
        current_state = table[current_state][symbol_check(*str)];
    }

    
    return head;
}
//Проверка ключевых слов и некоторых условий
Lex* checkKw(Lex* lex) {
    Lex* head = lex->next;
    while (lex->next) {
        if (lex->next->type == id) {
            
            if (!strcmp(lex->next->word, "end\0")) {
                lex->next->type = en;
            }
            if (!strcmp(lex->next->word, "case\0")) {
                lex->next->type = ca;
            }
                
            if (!strcmp(lex->next->word, "select\0")) {
                lex->next->type = se;
            }
            if (!strcmp(lex->next->word, "default\0")) {
                lex->next->type = de;

            }
        }
        if (lex->next->type == id) {
            if (strlen(lex->next->word) > 5) lex->next->type = wl;
        }

        lex->next = lex->next->next;
    }
    return head;

}

int synthAn(Lex* lex, statesSynth(*table)[12], ofstream& os) {
    Lex* p = lex;
    statesSynth current = s_S;
    int i = 0;
    while (p&&current!=en) {
        if (p->type != sp) {
            if (table[current][p->type] == s_Err) {
                os <<i << " ";


                switch (current) {
                case s_S: 
                    
                    os << "se";
                    break;
                case s_A:
                   
                    os << "id"<<" " << "vl";
                    break;
                case s_B:
                    
                    os << "ao";
                    break;
                case s_C:
                    
                    os << "id" << " " << "vl";
                    break;
                case s_D:
                    
                    os << "ca";
                    break;
                case s_E:
                   
                    os << "vl";
                    break;
                case s_F:
                    
                    os << "id";
                    break;
                case s_G:
                   
                    os << "eq";
                    break;
                case s_H:
                   
                    os << "id" << " " << "vl";
                    break;
                case s_I:
                   
                    os << "ao";
                    break;
                case s_J:
                  
                    os << "id"<<" "<<"vl";
                    break;
                case s_K:
                  
                    os << "ca"<<" " << "def";
                    break;
                case s_L:
                   
                    os << "id" << " " << "vl";
                    break;
                case s_M:
                  
                    os << "en";
                    break;

                } 
                return 1;
            }
            else {
                current = table[current][p->type];
            }
            i++;
        }
        p = p->next;
    }
    if (!lex) { os << "\n" << "0 se"; 
    return 1;
    }
    os << "OK";
    return 0;
}

int main()
{
    ifstream in("input.txt");
    ofstream out;
    in.seekg(0, ios::end);
    int n = in.tellg();
    char* str = new char[n + 1];
    in.seekg(0, ios::beg); // Перемещение каретки чтения файла на его начало
    in.read(&str[0], n);
    str[n] = '\0';
    in.close();

    states current_table[22][8];
    char typeName[12][2];
    statesSynth synth_table[15][12];

    table_creation(typeName);
    table_creation(current_table);
    table_creation(synth_table);

    Lex* head = LexAnalysis(str, current_table); // Вызов функции-анализатора
    head = checkKw(head);
    out.open("output.txt");
    Lex* cur = head;
    while (cur) {
        if (cur->type != sp) {
            out << cur->word;
            out << "[" << typeName[cur->type][0] << typeName[cur->type][1] << "] ";
            cout << cur->type<<" ";
        }
        cur = cur->next;
    }
    out << "\n";
   synthAn(head, synth_table, out);
    delete head;
    delete[] str;
   
    out.close();

}

