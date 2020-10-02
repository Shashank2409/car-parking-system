#include<bits/stdc++.h>
using namespace std;

string input_file_path = "input.txt" , output_file_path = "output.txt";

unordered_map<string , Car>car_info;

class Car{
    private:
        string car_no;
        int driver_age , parking_slot_no;
    public:
        void set_car_no(string car_no){
            this.car_no = car_no;
        }
        void set_driver_age(int driver_age){
            this.driver_age = driver_age;
        }
        void set_slot_no(int slot_no){
            this.parking_slot_no = slot_no;
        }
};

int main(){
    ifstream in(input_file_path.c_str());
    ofstream output(output_file_path.c_str()); 

    string input_line;
    while(getline(in , input_line)){
        cout<<input_line<<endl;
        stringstream words(input_line);
        string command;
        words>>command;
        if(command == "Create_parking_lot"){
            int no_of_slots;
            words>>no_of_slots;

        }
        else if(command == "Park"){
            string car_no , useless_string;
            int driver_age;
            words>>car_no>>useless_string>>driver_age;

        }
        else if(command == "Slot_numbers_for_driver_age"){
            int driver_age;
            words>>driver_age;
        }
        else if(command == "Slot_number_for_car_with_number"){
            string car_no;
            words>>car_no;
        }
        else if(command == "Leave"){
            int slot_no;
            words>>slot_no;

        }
        else if("Vehicle_registration_number_for_driver_of_age"){
            int driver_age;
            words>>driver_age;

        }
        else{
            cout<<"Invalid Command\n";
        }
    }
}