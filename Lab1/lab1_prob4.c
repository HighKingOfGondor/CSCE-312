
#include <stdio.h> //This is useful to do i/o to test the code
#include <stdlib.h>



unsigned int actuator_outputs;
unsigned int sensor_input;

void read_inputs_from_ip_if(){
    sensor_input = 0x11111111;
}

unsigned int set_actuator(unsigned int n, unsigned int bit)
{
    unsigned int re;
    if (bit)
    {
        actuator_outputs = actuator_outputs | (1 << n);
        re = actuator_outputs;
    }
    else
    {
        actuator_outputs = actuator_outputs & ~(1 << n);
        re = actuator_outputs;
    }
    return re;
}

unsigned int sensor_get_bit(unsigned int n)
{
    unsigned int returned_input;
    if((sensor_input & (1 << n)) != 0)
        returned_input = 1;
    else
        returned_input = 0;
    return returned_input;
}

unsigned int actuator_get_bit(unsigned int n)
{
    unsigned int returned_input;
    if((actuator_outputs & (1 << n)) != 0)
        returned_input = 1;
    else
        returned_input = 0;
    return returned_input;
}

unsigned int driver_on_seat()
{
    return sensor_get_bit(0);
}
unsigned int driver_seat_belt_fastened()
{
    return sensor_get_bit(1);
}
unsigned int engine_running()
{
    return sensor_get_bit(2);
}
unsigned int doors_closed()
{
    return sensor_get_bit(3);
}
unsigned int key_in_car()
{
    return sensor_get_bit(4);
}
unsigned int door_lock_lever()
{
    return sensor_get_bit(5);
}
unsigned int brake_pedal()
{
    return sensor_get_bit(6);
}
unsigned int car_moving()
{
    return sensor_get_bit(7);
}

unsigned int bell(unsigned int n)
{
    return set_actuator(0, n);
}
unsigned int door_lock_actuator(unsigned int n)
{
    return set_actuator(1, n);
}
unsigned int brake_actuator(unsigned int n)
{
    return set_actuator(2, n);
}

void write_output_to_op_if()
{
    //place your output code here
    //to display/print the state of the 3 actuators (DLA/BELL/BA)
    
    printf("driver_seat_belt_fastened: %d\n", driver_seat_belt_fastened());
    printf("engine_running: %d\n", engine_running());
    printf("driver_on_seat: %d\n", driver_on_seat());
    printf("doors_closed: %d\n", doors_closed());
    printf("key_in_car: %d\n", key_in_car());
    printf("door_lock_lever: %d\n", door_lock_lever());
    printf("brake_pedal: %d\n", brake_pedal());
    printf("car_moving: %d\n", car_moving());
    
    printf("Bell: %d\n", actuator_get_bit(0));
    printf("Lock: %d\n", actuator_get_bit(1));
    printf("Brake: %d\n", actuator_get_bit(2));
    if(actuator_outputs & 1)
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
    
    if (engine_running() && (!doors_closed() || !driver_seat_belt_fastened()))
    {
        bell(1);
    }
    else
        bell(0);
    
    if (!driver_on_seat() && key_in_car())
        door_lock_actuator(0);
    else if (door_lock_lever() && driver_on_seat())
        door_lock_actuator(1);
    else
        door_lock_actuator(0);
    
    if (brake_pedal() && car_moving())  // Use the aANDb_function
        brake_actuator(1);
    else
        brake_actuator(0);
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
