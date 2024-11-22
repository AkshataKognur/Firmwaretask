#include <iostream>
#include <serial/serial.h> 

using namespace std;
double calculateSpeed(double startTime, size_t bytesSent) {
    double elapsedTime = clock() - startTime;
    elapsedTime /= CLOCKS_PER_SEC;
    return (bytesSent * 8) / elapsedTime; 
}

int main() {
    try {
        serial::Serial mySerial("COM_PORT", 2400, serial::Timeout::simpleTimeout(1000)); // Replace COM_PORT with your actual port

        string textToSend = "Finance Minister Arun Jaitley Tuesday hit out at former RBI governor Raghuram Rajan "
                            "economist at IMF warned of impending financial crisis of 2008...";
        size_t bytesSent = textToSend.size();
        
        double startTime = clock();
        mySerial.write(textToSend);


        double speed = calculateSpeed(startTime, bytesSent);
        cout << "Transmission Speed: " << speed << " bits/second" << endl;

        string receivedData;
        mySerial.read(receivedData, bytesSent);
        cout << "Received Data: " << receivedData << endl;

    } catch (const serial::IOException& e) {
        cerr << "Error opening serial port: " << e.what() << endl;
        return -1;
    }

    return 0;
}