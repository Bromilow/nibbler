#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    clock_t current_ticks, delta_ticks;
    clock_t fps = 0;
    int     i = 0;

    while(true)// your main loop. could also be the idle() function in glut or whatever
    {
        ++i;
        cout << "counter : " << i << endl;

        current_ticks = clock();

        cout << "curr_ticks : " << current_ticks << endl;

        delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene

        cout << "delta_ticks : " << delta_ticks << endl;

        if(delta_ticks > 0) {
            fps = CLOCKS_PER_SEC / delta_ticks;
            cout << "curr_fps : " << fps << endl;
        }
    }
    return (0);
}