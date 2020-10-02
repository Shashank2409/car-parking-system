#include<bits/stdc++.h>
using namespace std;

string input_file_path = "input.txt" , output_file_path = "output.txt";

class Car{
    private:
        string car_no;
        int driver_age , parking_slot_no;
    public:
        Car(string car_no , int driver_age , int parking_slot_no){
            this->car_no = car_no;
            this->driver_age = driver_age;
            this->parking_slot_no = parking_slot_no;
        }
        void set_car_no(string car_no){
            this->car_no = car_no;
        }
        void set_driver_age(int driver_age){
            this->driver_age = driver_age;
        }
        void set_slot_no(int slot_no){
            this->parking_slot_no = slot_no;
        }
};

unordered_map<string , Car>regNo_Car;
unordered_map<int , unordered_set<Car>>driverAge_Car;
unordered_map<int , Car>slotNo_Car; 

class CarParking{
    private:
        int no_of_slots;
        priority_queue<int , vector<int> , greater<int>>available_slots;
        vector<bool>alloted_slots;
    public:
        CarParking(){
            this->no_of_slots = 0;
        }
        string set_slots(int no_of_slots){
            string response , no_of_slots_string;

            this->no_of_slots = no_of_slots;
            alloted_slots.push_back(false);
            for(int slot = 1; slot <= no_of_slots; slot++){
                available_slots.push(slot);
                alloted_slots.push_back(false);
            }

            stringstream int_to_string(no_of_slots);
            int_to_string>>no_of_slots_string;
            response = "Created parking of " + no_of_slots_string + " slots\n";

            return response;            
        }
        string park(string car_no , int driver_age){
            string response;
            if(priority_queue.size() == 0){
                response = "No parking slot available\n";
            }
            else{
                int alloted_slot_no = available_slots.top();
                available_slots.pop();
                alloted_slots[alloted_slot_no] = true;

                Car car = new Car(car_no , driver_age , alloted_slot_no);
                regNo_Car.insert({car_no , car});
                driverAge_Car[driver_age].insert(car);
                slotNo_Car.insert({alloted_slot_no , car});

                stringstream string_to_int(car_no);
                string car_no_string;
                string_to_int>>car_no_string;
                response = "Car with vehicle registration number \"" + car_no + "\" has been parked at slot number " + car_no_string + "\n";
            }
            return response;
        }

        vector<int> slot_no_for_driver_age(int driver_age){
            vector<int>ages;
            for(auto it = driverAge_Car.begin(); it != driverAge_Car.end(); it++){
                ages.push_back((it->second)->parking_slot_no);
            }
            return ages;
        }

        int slot_no_for_car_with_no(string car_no){
            auto it = slotNo_Car.find(car_no);
            if(it == slotNo_Car.end()){
                return -1;
            }
            int slot_no_for_car = it->slot_no;
            return slot_no_for_car;
        }

        vector<string> vehicle_no_for_car_with_driver_age(int driver_age){
            vector<string>vehicle_nos;
            for(auto it = driverAge_Car.begin(); it != driverAge_Car.end(); it++){
                vehicle_nos.push_back((it->second)->car_no);
            }
            return vehicle_nos;
        }

        string leave(int slot_no){
            string response;
            if(alloted_slots[slot_no] == false){
                response = "The slot is already empty\n";
            }
            else{
                alloted_slots[slot_no] = false;
                Car car = slotNo_Car[slot_no];
                slotNo_Car.erase(slot_no);
                regNo_Car.erase(car->car_no);
                driverAge_Car[car->driver_age].erase(car);
                available_slots.push(slot_no);

                stringstream age_to_string(driver_age) , slotNo_to_string(slot_no);
                string slot_no_string , driver_age_string;
                slotNo_to_string>>slot_no_string;
                age_to_string>>driver_age_string;
                response = "Slot number " + slot_no_string + " vacated, the car with vehicle registration number \"" + car->car_no +"\"left the space, the driver of the car was of age " + driver_age_string + "\n";
            }
            return response;
        }

};

int main(){
    ifstream in(input_file_path.c_str());
    ofstream output(output_file_path.c_str()); 

    string input_line;
    CarParking parking_area;

    while(getline(in , input_line)){
        cout<<input_line<<endl;
        stringstream words(input_line);
        string command;
        words>>command;
        
        if(command == "Create_parking_lot"){
            int no_of_slots;
            words>>no_of_slots;
            parking_area.set_slots(no_of_slots);
        }
        else if(command == "Park"){
            string car_no , useless_string , response;
            int driver_age;
            words>>car_no>>useless_string>>driver_age;
            if(parking_area != NULL){
                response = parking_area.park(car_no , driver_age);
            }
            else{
                response = "We do not own a parking area yet\n";
            }
            cout<<response;
        }
        else if(command == "Slot_numbers_for_driver_age"){
            int driver_age;
            words>>driver_age;
            vector<int>ages = parking_area.slot_no_for_driver_age(driver_age);
            for(int driver = 0; driver < ages.size(); driver++){
                cout<<ages[driver]<<(driver == (ages.size() - 1)?"":",");
            }
            cout<<"\n";
        }
        else if(command == "Slot_number_for_car_with_number"){
            string car_no;
            words>>car_no;
            int slot_no_for_car = parking_area.slot_no_for_car_with_no(car_no);
            if(slot_no_for_car == -1){
                cout<<"No such car exists\n";
            }
            else{
                cout<<slot_no_for_car<<"\n";
            }
        }
        else if(command == "Leave"){
            int slot_no;
            words>>slot_no;
            string response = parking_area.leave(slot_no);
            cout<<response;
        }
        else if("Vehicle_registration_number_for_driver_of_age"){
            int driver_age;
            words>>driver_age;
            string vehicle_no = parking_area.vehicle_no_for_car_with_driver_age(driver_age);
            for(int vehicle = 0; vehicle < vehicle_no.size(); vehicle++){
                cout<<ages[vehicle]<<(vehicle == (vehicle_no.size() - 1)?"":",");
            }
            cout<<"\n";
        }
        else{
            cout<<"Invalid Command\n";
        }
    }
}