#include <iostream>
using namespace std;

#define MAX 5   // fixed buffer size

class CircularQueue {
private:
    int sensorData[MAX];
    int front, rear;

public:
    CircularQueue() {
        front = -1;
        rear = -1;
    }

    // Insert sensor reading
    void enqueue(int value) {
        if ((rear + 1) % MAX == front) {
            cout << "Buffer full! Overwriting oldest reading.\n";
            front = (front + 1) % MAX;
        }

        if (front == -1)
            front = 0;

        rear = (rear + 1) % MAX;
        sensorData[rear] = value;
        cout << "Sensor reading stored: " << value << endl;
    }

    // Remove oldest reading
    void dequeue() {
        if (front == -1) {
            cout << "No sensor readings available!\n";
            return;
        }

        cout << "Removed sensor reading: " << sensorData[front] << endl;

        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % MAX;
        }
    }

    // Display all readings
    void display() {
        if (front == -1) {
            cout << "No sensor data in buffer!\n";
            return;
        }

        cout << "Current Sensor Readings: ";
        int i = front;
        while (true) {
            cout << sensorData[i] << " ";
            if (i == rear)
                break;
            i = (i + 1) % MAX;
        }
        cout << endl;
    }
};

int main() {
    CircularQueue cq;
    int choice, value;

    while (1) {
        cout << "\nSmart Forest Fire Detection - Sensor Buffer\n";
        cout << "1. Add sensor reading\n";
        cout << "2. Remove oldest reading\n";
        cout << "3. Display sensor readings\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter sensor reading (temperature/smoke): ";
                cin >> value;
                cq.enqueue(value);
                break;

            case 2:
                cq.dequeue();
                break;

            case 3:
                cq.display();
                break;

            case 4:
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }
}
