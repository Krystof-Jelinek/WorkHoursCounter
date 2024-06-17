#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <variant>
#include <optional>
#include <compare>
#include <charconv>
#include <span>
#include <utility>

using namespace std;

class CProgram{
    public:
    int months_left = 0;
    int average_meetings = 2;
    int worst_case_meetings = 4;
    bool first = false;

    CProgram(){}

    CProgram(int mons, bool f){
        months_left = mons;
        first = f;
    }

};

class CTimerManager{
    public:
    vector<CProgram> cur_programs;
    int cur_month = 0;

    CTimerManager(){
        cur_programs.clear();
    }

    void inicialize(){
        cout << "---------------------- Načítám ze souboru ----------------------" << endl;

        ifstream MyReadFile("data.txt");
        while(!MyReadFile.eof()){
            count_month_hours_from_file(MyReadFile);
        }

        cout << "---------------------- Konec načítání ze souboru ----------------------" << endl << endl;
    }

    void count_month_hours(){
        cout << "---------------------- Vstup měsíčních dat ----------------------" << endl;
        cout << "Počet Lidí kteří zrušili vstupní domluvenou hodinovou schůzku:";
        int wasted_hours = 0;
        cin >> wasted_hours;

        cout << "Prosím zadejte programy přijaté v tomto měsíci:" << endl;
        for(int mesice = 3; mesice <= 24;){
           cout << "Akutální počet " + to_string(mesice) + " měsíčních programů:";
            int program_number = 0;
            cin >> program_number;
            for(int i = 0; program_number > i; program_number--){
                cur_programs.push_back({mesice, true});
            }
            if(mesice < 10){
                mesice += 3;
            }
            else{
                mesice += 6;
            }
        }

        double montly_hours = 0;
        double worst_case_hours = 0;


        for(CProgram & cur : cur_programs){
            if((cur.first) && (cur.months_left > 0)){
                cur.first = false;
                montly_hours++;
                worst_case_hours++;
                
                double tmp = (double (cur.average_meetings - 1))/2;
                montly_hours = montly_hours + tmp;
                
                double worst_tmp = (double(cur.worst_case_meetings - 1))/2;
                worst_case_hours = worst_case_hours + worst_tmp;

                cur.months_left--;
            }

            else if(cur.months_left > 0){
                double tmp = double(cur.average_meetings)/2;
                montly_hours = montly_hours + tmp;

                double worst_tmp = double(cur.worst_case_meetings) /2;
                worst_case_hours = worst_case_hours + worst_tmp;

                cur.months_left--;
            }
        }

        for(auto itr = cur_programs.begin(); itr != cur_programs.end();){
            if(itr->months_left <= 0){
                itr = cur_programs.erase(itr);
            }
            else{
                itr++;
            }
        }

        montly_hours += wasted_hours;
        worst_case_hours += wasted_hours;
        cout << "Měsíc číslo: " + to_string(cur_month) << endl;
        cout << "V Tomto měsící je nutné si v průmerném případě vyhradit na schůze " + to_string(montly_hours) + " hodin" << endl;
        cout << "V Tomto měsící je nutné si v nejhorším případě vyhradit na schůze " + to_string(worst_case_hours) + " hodin" << endl;
        cout << "---------------------- Konec Měsíce ----------------------" << endl << endl;
        cur_month++;
    }

    void count_month_hours_from_file(ifstream & filestream){

        string input_line;

        //get rid of month line
        getline(filestream, input_line);

        cout << input_line << endl;
        cout << "---------------------- Vstup měsíčních dat ----------------------" << endl;
        cout << "Počet Lidí kteří zrušili vstupní domluvenou hodinovou schůzku:";
        int wasted_hours = 0;

        //wasted hours time
        getline(filestream, input_line);
        wasted_hours = stoi(input_line.substr(16));
        cout << " " + to_string(wasted_hours) << endl;

        cout << "Prosím zadejte programy přijaté v tomto měsíci:" << endl;
        for(int mesice = 3; mesice <= 24;){
            cout << "Akutální počet " + to_string(mesice) + " měsíčních programů:";
            int program_number = 0;
            getline(filestream, input_line);
            if(mesice < 10){
                program_number = stoi(input_line.substr(7));
            }
            else{
                program_number = stoi(input_line.substr(8));
            }
            cout << " " + to_string(program_number) << endl;

            for(int i = 0; program_number > i; program_number--){
                cur_programs.push_back({mesice, true});
            }
            if(mesice < 10){
                mesice += 3;
            }
            else{
                mesice += 6;
            }
        }
        //get rid of the newline
        getline(filestream, input_line);

        double montly_hours = 0;
        double worst_case_hours = 0;


        for(CProgram & cur : cur_programs){
            if((cur.first) && (cur.months_left > 0)){
                cur.first = false;
                montly_hours++;
                worst_case_hours++;
                
                double tmp = (double (cur.average_meetings - 1))/2;
                montly_hours = montly_hours + tmp;
                
                double worst_tmp = (double(cur.worst_case_meetings - 1))/2;
                worst_case_hours = worst_case_hours + worst_tmp;

                cur.months_left--;
            }

            else if(cur.months_left > 0){
                double tmp = double(cur.average_meetings)/2;
                montly_hours = montly_hours + tmp;

                double worst_tmp = double(cur.worst_case_meetings) /2;
                worst_case_hours = worst_case_hours + worst_tmp;

                cur.months_left--;
            }
        }

        for(auto itr = cur_programs.begin(); itr != cur_programs.end();){
            if(itr->months_left <= 0){
                itr = cur_programs.erase(itr);
            }
            else{
                itr++;
            }
        }

        montly_hours += wasted_hours;
        worst_case_hours += wasted_hours;
        cout << "V Tomto měsící je nutné si v průmerném případě vyhradit na schůze " + to_string(montly_hours) + " hodin" << endl;
        cout << "V Tomto měsící je nutné si v nejhorším případě vyhradit na schůze " + to_string(worst_case_hours) + " hodin" << endl;
        cout << "---------------------- Konec Měsíce ----------------------" << endl << endl;
        cur_month++;
    }

};




int main(void){

    CTimerManager x;
    x.inicialize();

    while(true){
        x.count_month_hours();
    }



    return 0; 
}