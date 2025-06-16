#include <iostream>
#include <string>
#include "view.h"
#include "controller.h"
#include "AnsiPrint.h"

int main(){
    // TODO 
    // Integrate the Simple MVC Pattern to run the program.
	View view;                
    Controller controller(view);  
    
    controller.run();


	return 0;
}
