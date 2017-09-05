
#include "rtc.h"


using namespace std;

int main()
{
    set_term();

    cout << "Hello world!" << endl;
    cout<<setbase(16);  /// needed so BCD displays correctly

    char* NISTbuffer;
	NISTbuffer = new char[100];
	stringstream my_ss;
	string myTime;
	string myDate;

	buf_pitime(NISTbuffer);

	I2CBus myFP(1, I2C_SLAVE_ADDR_RTC);     // start I2C for RTC
    lcddisplay myLCD;                       // start for LCD
	myLCD.lcd_clear();
	myLCD.set_color(200,200,200);



    uint8_t* p_timekeep = new uint8_t[8];
    int okornot= myFP.device_read_block(TIMEKEEPSTART, 7, p_timekeep);

    cout<<"Timekeep: "
        <<(p_timekeep[2] & 0x3f) <<":"          // hours
        <<(p_timekeep[1] & 0x7f) <<":"          // minutes
        <<(p_timekeep[0] & 0x7f) <<":"<<endl    // seconds
        <<"Date: "
        <<(p_timekeep[5] & 0x1f) <<":"          // month
        <<(p_timekeep[4] & 0x3f) <<":"          // date
        <<(p_timekeep[6] & 0xff) <<":"          // year
        <<(p_timekeep[3] & 0x07) <<":"          // day of week
        <<endl;

    my_ss <<setbase(16)<<(p_timekeep[2] & 0x3f) <<":"          // hours
            <<(p_timekeep[1] & 0x7f) <<":"          // minutes
            <<(p_timekeep[0] & 0x7f); //<<endl    // seconds

    my_ss >> myTime;
    my_ss.clear();

    my_ss <<(p_timekeep[5] & 0x1f) <<"-"          // month
        <<(p_timekeep[4] & 0x3f) <<"-"          // date
        <<(p_timekeep[6] & 0xff); // <<":"          // year
        //<<(p_timekeep[3] & 0x07);          // day of week
        //<<endl;

    my_ss >> myDate;

    cout<<"my time "<<myTime<<endl;
    cout<<"my date "<<myDate<<endl;

    //myLCD.lcd_write(myTime);
    myLCD << myTime;
    myLCD.lcd_set_cursor_address(0x40);
    //myLCD.lcd_write(myDate);
    myLCD << myDate;
    sleep(2);
    myLCD.lcd_clear();

    vector<char> vecnist(100);
	strcpy(&vecnist[0], NISTbuffer);	// STD reference page 278
	vecnist.shrink_to_fit();

	string mynist(NISTbuffer);
	string line_1 = mynist.substr(7, 8);
	string line_2 = mynist.substr(16, 8);

	size_t found;
	cout << line_1 << endl;
	cout << line_2 << endl;
	found = mynist.find("UTC");
	string line_3 = mynist.substr(found, 9);
	cout << line_3 << endl;
	cout << mynist << endl;

	//myLCD.lcd_write(NISTbuffer);
	//sleep(1);
	myLCD.lcd_set_cursor_address(0x00);
	//myLCD.lcd_write(line_3);
	myLCD << line_3;
	//myLCD.lcd_write("Time");
	myLCD << "Time";
	myLCD.lcd_set_cursor_address(0x40);
	//myLCD.lcd_write(line_1);
	myLCD << line_1;
	//myLCD.lcd_write(line_2);
	myLCD << line_2;
	sleep(1);

	myLCD.lcd_clear();
	myLCD.lcd_set_cursor_address(0x00);
	//myLCD.lcd_write("RTC  ");
	myLCD << "RTC  ";
	//myLCD.lcd_write(myTime);
	myLCD << myTime;
	myLCD.lcd_set_cursor_address(0x40);
	//myLCD.lcd_write("NIST ");
	myLCD << "NIST ";
	//myLCD.lcd_write(line_2);
	myLCD << line_2;
    sleep(2);


    myFP.closei2c();
    return 0;
}


int set_term()
{
    struct termios term;

    const char* portname = "/dev/ttyACM0";

    int usbFD = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (usbFD < 0)
    {
        cout<<"error %d opening %s: %s"<<endl;
        return 0;
    }

    term.c_cflag = BAUDRATE | CS8 | CSTOPB |CLOCAL | CREAD;
    term.c_iflag = 0;
    term.c_oflag = 0;
    term.c_lflag = 0;
    tcflush(usbFD, TCIFLUSH);
    tcsetattr(usbFD, TCSANOW, &term);
    close(usbFD);
    return 0;
}


