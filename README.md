#car - parking - system

This file contains the functionalities of the methods and classes present in the code.

GLOBAL VARIABLES

    1. string input_file_path
        This variable stores the path of the file in which the input is stored.
    2. string output_file_path
        This variable stores the path of the file in which the ouptut will get saved after the execution of the program.
    3. map<string , Car> regNo_Car
        This Map stores key-value pairs with car_registration_no as key and the Car class object as value.
    4. map<int , vector<Car> > driverAge_Car
        This map stores key-value pairs with driver_age as key and vector of Car class objects with age == driver_age as value.
    5. map<int , Car> slotNo_Car
        This map stores key-value pairs with slot_no as key and the Car class object as value.

CLASSES

    1. Car
        This class represents a car in the question. The attributes of the class are 
            car_no which represents the vehicle registration no
            driver_age which represents the age of the driver of the car and
            parking_slot_no which represents on which slot no the car is parked.
        The class contains a defalut constructor, a parameterized constructor and different getter and setter methods for all the fields.

    2. CarParking
        This class represents a parking lot given in the question. The attributes of the class are
            no_of_slots which represents the total no of slots present in the parking lot
            available slots which is a priority queue for storing the available slots in sorted order i.e., the slot nearest to the entry will be in the front of the priority queue and
            no_of_alloted_slots which stores whether a slot is available or not

        The class contains a default constuctor for initializing the no_of_slots integer. Below is the description of other methods present in the CarParking class :-
            a. set_slots method
                It is called on the command "Create_parking_lot" and it sets the no_of_slots attribute of the class as the total on of slots present in the parking lot. Also, it initializes the alloted_slots as false for all the slots and pushes all the slots in the priority queue.
            b. park method
                It is called on the command "Park" and creates an object of the Car class. The object attributes are set to the given paramters and the object is inserted into regNo_Car, driverAge_Car and slotNo_Car maps. The slot nearest to the entry is marked as unavailable and the car is parked on that slot.
            c. slot_no_for_driver_age method
                It is called on the command "Slot_numbers_for_driver_of_age" and it returns a vector which consists of all the slot numbers on which the cars with driver of the given age are parked. 
            d. slot_no_for_car_with_no method
                It is called on the command "Slot_number_for_car_with_number" and it returns an interger representing the slot no on which the car with given registration number is parked.
            e. vehicle_no_for_car_with_driver_age method 
                It is called on the command "Vehicle_registration_number_for_driver_of_age" and it returns a vector which consists of all the vehicle registration numbers of cars which have drivers of the given age.
            f. leave method
                It is called on the command "Leave" and it deletes the car parked on the given slot from the regNo_Car, driverAge_Car and slotNo_Car maps, marks the slot as available in the available_slots vector and adds the slot in the alloted_slots priority queue.  



