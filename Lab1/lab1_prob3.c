// CSCE312: Lab-1 Problem-3 framework

/* ***   README   **** */

/*
 This example program sounds the bell when driver is on seat
 AND haven't closed the doors. Use the general framework and the function
 shells, replace the code inside  the control_action() function with your
 own code to do problems 3 and 4.
 
 Note: This code is designed to run in an infinite loop to mimic a real control system.
 If you prefer to read the inputs from a file, modify the code appropriately to terminate the
 loop when all the inputs have been processed.
  
 run this file as : gcc filename.c -o executableName
 
 */


#include <stdio.h> //This is useful to do i/o to test the code
#include <stdlib.h>

unsigned int bell;
unsigned int door_lock_actuator;
unsigned int brake_actuator;

unsigned int driver_seat_belt_fastened;
unsigned int engine_running;
unsigned int driver_on_seat;
unsigned int doors_closed;
unsigned int key_in_car;
unsigned int door_lock_lever;
unsigned int brake_pedal;
unsigned int car_moving;

void read_inputs_from_ip_if()
{
    FILE *my_file;
    my_file = fopen("status.txt", "r");
    fscanf(my_file, "%d %d %d %d %d %d %d %d", &driver_on_seat, &doors_closed, &driver_seat_belt_fastened, &engine_running, &key_in_car, &door_lock_lever, &brake_pedal, &car_moving);
    fclose(my_file);
}

void write_output_to_op_if()
{
    //place your output code here
    //to display/print the state of the 3 actuators (DLA/BELL/BA)
    printf("driver_seat_belt_fastened: %d\n", driver_seat_belt_fastened);
    printf("engine_running: %d\n", engine_running);
    printf("driver_on_seat: %d\n", driver_on_seat);
    printf("doors_closed: %d\n", doors_closed);
    printf("key_in_car: %d\n", key_in_car);
    printf("door_lock_lever: %d\n", door_lock_lever);
    printf("brake_pedal: %d\n", brake_pedal);
    printf("car_moving: %d\n", car_moving);
    
    printf("Bell: %d\n", bell);
    printf("Lock Actuator: %d\n", door_lock_actuator);
    printf("Brake Actuator: %d\n", brake_actuator);
    if(bell)
        exit(0);
}


//The code segment which implements the decision logic
void control_action()
{
    /*
     The code given here sounds the bell when driver is on seat
     AND hasn't closed the doors. (Requirement-2)
     Replace this code segment with your own code to do problems 3 and 4.
     */
    
    if (driver_on_seat && (!doors_closed || !driver_seat_belt_fastened))
        bell = 1;
    else
        bell = 0;
    
    if (!driver_on_seat && key_in_car)
        door_lock_actuator = 0;
    else if (door_lock_lever && driver_on_seat)
        door_lock_actuator = 1;
    else
        door_lock_actuator = 0;
    
    if (brake_pedal && car_moving)  // Use the aANDb_function
        brake_actuator = 1;
    else
        brake_actuator = 0;
}

/* ---     You should not have to modify anything below this line ---------*/

int main(int argc, char *argv[])
{
    /*The main control loop which keeps the system alive and responsive for ever,
     until the system is powered off */
    for ( ; ; )
    {
        read_inputs_from_ip_if();
        control_action();
        write_output_to_op_if();
        
    }
    return 0;
}
