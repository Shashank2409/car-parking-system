#include<bits/stdc++.h>
using namespace std;

/*Path for the input and output files*/
string input_file_path = "input.txt" , output_file_path = "output.txt";

class Car{
    private:
        string car_no;
        int driver_age , parking_slot_no;
        
    public:
    	/*Constructors for the class Car*/
    	Car(){
    		this->car_no = "";
    		this->driver_age = -1;
    		this->parking_slot_no = -1;
		}
        Car(string car_no , int driver_age , int parking_slot_no){
            this->car_no = car_no;
            this->driver_age = driver_age;
            this->parking_slot_no = parking_slot_no;
        }
        
        /*Getters and Setters for the class Car*/
        int get_slot_no(){
        	return this->parking_slot_no;
		}
		void set_slot_no(int slot_no){
            this->parking_slot_no = slot_no;
        }
        
		string get_car_no(){
			return this->car_no; 
		}
		void set_car_no(string car_no){
            this->car_no = car_no;
        }
    
		int get_driver_age(){
			return this->driver_age;
		}
        void set_driver_age(int driver_age){
            this->driver_age = driver_age;
        }
};

/*Map with car_registration_no as key and the Car class object as value*/
map<string , Car> regNo_Car;

/*Map with driver_age as key and vector of Car class objects with age == driver_age as value*/
map<int , vector<Car> > driverAge_Car;

/*Map with slot_no as key and the Car class object as value*/
map<int , Car> slotNo_Car; 

class CarParking{
    private:
        int no_of_slots;
        priority_queue<int , vector<int> , greater<int> >available_slots;
        vector<bool>alloted_slots;
    public:
        CarParking(){
            this->no_of_slots = 0;
        }
        
        /*Method for converting an integer to string*/
        string int_to_string(int convertFrom){
        	ostringstream str1; 
		    str1 << convertFrom; 
		    string convertTo = str1.str();
        	return convertTo;
		}
        
        /*Method for initializing the Car Parking Area with a given number of slots*/
        string set_slots(int no_of_slots){
            string response , no_of_slots_string = int_to_string(no_of_slots);

            this->no_of_slots = no_of_slots;
            alloted_slots.push_back(false);
            for(int slot = 1; slot <= no_of_slots; slot++){
                available_slots.push(slot);
                alloted_slots.push_back(false);
            }
			
            response = "Created parking of " + no_of_slots_string + " slots\n";

            return response;            
        }
        
        /*Method for parking a car in the car parking area at the nearest slot from the entry*/
        string park(string car_no , int driver_age){
            string response;
            if(available_slots.size() == 0){
                response = "No parking slot available\n";
            }
            else{
                int alloted_slot_no = available_slots.top();
                available_slots.pop();
                alloted_slots[alloted_slot_no] = true;

                Car car(car_no , driver_age , alloted_slot_no);
                regNo_Car.insert({car_no , car});
                driverAge_Car[driver_age].push_back(car);
                slotNo_Car.insert({alloted_slot_no , car});

                string slot_no_string = int_to_string(alloted_slot_no);
                response = "Car with vehicle registration number \"" + car_no + "\" has been parked at slot number " + slot_no_string + "\n";
            }
            return response;
        }

		/*Method for getting the slot nos on which the cars with drivers of given ages are parked*/
        vector<int> slot_no_for_driver_age(int driver_age){
            vector<int>ages;
            for(int i = 0; i < driverAge_Car[driver_age].size(); i++){
                ages.push_back(driverAge_Car[driver_age][i].get_slot_no());
            }
            return ages;
        }

		/*Method for getting the slot no of the car with the given car_registration_no*/
        int slot_no_for_car_with_no(string car_no){
            map<string , Car>::iterator it = regNo_Car.find(car_no);
            if(it == regNo_Car.end()){
                return -1;
            }
            int slot_no_for_car = (it->second).get_slot_no();
            return slot_no_for_car;
        }

		/*Method for getting the car_registration_no of the cars having drivers of the given age*/
        vector<string> vehicle_no_for_car_with_driver_age(int driver_age){
            vector<string>vehicle_nos;
            map<int , vector<Car> >::iterator it = driverAge_Car.find(driver_age);
            if(it == driverAge_Car.end()){
            	return vehicle_nos;
			}
			
            vector<Car> cars = it->second;
            for(int i = 0; i<  cars.size(); i++){
                vehicle_nos.push_back(cars[i].get_car_no());
            }
            return vehicle_nos;
        }

		/*Method called when a car is leaving the parking area*/
        string leave(int slot_no){
            string response;
            if(alloted_slots[slot_no] == false){
                response = "The slot is already empty\n";
            }
            else{
                alloted_slots[slot_no] = false;
                map<int , Car>::iterator it_car = slotNo_Car.find(slot_no);
                
                Car car = it_car->second;
                int driver_age = car.get_driver_age();
                slotNo_Car.erase(slot_no);
                regNo_Car.erase(car.get_car_no());
                
                map<int , vector<Car> >::iterator it_map = driverAge_Car.find(driver_age);
				vector<Car>::iterator it_vector = (it_map->second).begin();
				
                for(; it_vector != (it_map->second).end(); it_vector++){
                	if((*it_vector).get_car_no() == car.get_car_no()){
                		(it_map->second).erase(it_vector);
                		break;
					}
				}
                
                available_slots.push(slot_no);

                string slot_no_string = int_to_string(slot_no), driver_age_string = int_to_string(driver_age), car_no_string = car.get_car_no();
                
                response = "Slot number " + slot_no_string + " vacated, the car with vehicle registration number \"" 
                + car_no_string +"\" left the space, the driver of the car was of age " + driver_age_string + "\n";
            }
            return response;
        }

};

int main(){
    ifstream in(input_file_path.c_str());
    ofstream out(output_file_path.c_str()); 

    string input_line;
    CarParking parking_area;

    while(getline(in , input_line)){
        stringstream words(input_line);
        string command;
        words >> command;
        
        /*Block for creating a new parking lot*/
        if(command == "Create_parking_lot"){
            int no_of_slots;
            words >> no_of_slots;
            string response = parking_area.set_slots(no_of_slots);
            cout << response;
            out << response;
        }

        /*Block for parking a car*/
        else if(command == "Park"){
            string car_no , useless_string , response;
            int driver_age;
            words >> car_no >> useless_string >> driver_age;
            response = parking_area.park(car_no , driver_age);
            
            cout << response;
            out << response;
        }

        /*Block for getting the slot numbers where cars of drivers with the given age are parked*/
        else if(command == "Slot_numbers_for_driver_of_age"){
            int driver_age;
            words >> driver_age;
            vector<int>ages = parking_area.slot_no_for_driver_age(driver_age);
            for(int driver = 0; driver < ages.size(); driver++){
                cout << ages[driver] << (driver == (ages.size() - 1)?"":",");
				out << ages[driver] << (driver == (ages.size() - 1)?"":",");
            }
            cout << "\n";
            out << "\n";
        }

        /*Block for getting the slot number of the car with the given registration_number*/
        else if(command == "Slot_number_for_car_with_number"){
            string car_no;
            words >> car_no;
            int slot_no_for_car = parking_area.slot_no_for_car_with_no(car_no);
            if(slot_no_for_car == -1){
                cout << "null\n";
                out << "null\n";
            }
            else{
                cout << slot_no_for_car << "\n";
                out << slot_no_for_car << "\n";
            }
        }

        /*Block called when a car is leaving*/
        else if(command == "Leave"){
            int slot_no;
            words >> slot_no;
            string response = parking_area.leave(slot_no);
            cout << response;
            out << response;
        }

        /*Block for getting the registration_no of cars with drivers of the given age*/
        else if("Vehicle_registration_number_for_driver_of_age"){
            int driver_age;
            words >> driver_age;
            vector<string> vehicle_no = parking_area.vehicle_no_for_car_with_driver_age(driver_age);
            for(int vehicle = 0; vehicle < vehicle_no.size(); vehicle++){
                cout << vehicle_no[vehicle] << (vehicle == (vehicle_no.size() - 1)?"":",");
                out << vehicle_no[vehicle] << (vehicle == (vehicle_no.size() - 1)?"":",");
            }
            if(vehicle_no.size() == 0){
            	cout << "null";
            	out << "null";
			}
            cout << "\n";
            out << "\n";
        }

        /*Block when any invalid command is called*/
        else{
            cout << "Invalid Command\n";
            out << "Invalid Command\n";
        }
    }
}