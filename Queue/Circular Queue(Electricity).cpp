#include <iostream>
#include <string>

using namespace std;

struct OutageTask {
    int taskID;               // Unique outage ID
    string substationName;    // Substation affected
    string issue;             // Type of issue (e.g., Transformer fault, Line down)
};

class CircularQueue {
    int front, rear, size;
    int capacity;
    OutageTask* queue;

public:
    CircularQueue(int cap) {
        capacity = cap;
        queue = new OutageTask[capacity];
        front = -1;
        rear = -1;
        size = 0;
    }

    ~CircularQueue() {
        delete[] queue;
    }

    bool isFull() {
        return size == capacity;
    }

    bool isEmpty() {
        return size == 0;
    }

    void enqueue(OutageTask task) {
        if (isFull()) {
            cout << "Queue full! Cannot add new outage task.\n";
            return;
        }
        rear = (rear + 1) % capacity;
        queue[rear] = task;
        if (front == -1) front = rear;
        size++;
        cout << "Task ID " << task.taskID << " added for substation " << task.substationName << endl;
    }

    OutageTask dequeue() {
        if (isEmpty()) {
            cout << "Queue empty! No tasks to handle.\n";
            return {-1, "", ""};
        }
        OutageTask task = queue[front];
        front = (front + 1) % capacity;
        size--;
        if (size == 0) front = rear = -1; // reset queue
        return task;
    }

    void displayQueue() {
        if (isEmpty()) {
            cout << "No pending outage tasks.\n";
            return;
        }
        cout << "Pending Outage Tasks:\n";
        int i = front;
        for (int cnt = 0; cnt < size; cnt++) {
            cout << "Task ID: " << queue[i].taskID
                 << ", Substation: " << queue[i].substationName
                 << ", Issue: " << queue[i].issue << endl;
            i = (i + 1) % capacity;
        }
    }
};

int main() {
    int capacity;
    cout << "Enter max number of outage tasks to store: ";
    cin >> capacity;

    CircularQueue outageQueue(capacity);

    int choice = 0;
    int taskCounter = 1;
    while (true) {
        cout << "\n1: Add Outage Task\n2: Handle Next Task\n3: View Pending Tasks\n4: Exit\nChoose option: ";
        cin >> choice;

        if (choice == 1) {
            OutageTask task;
            task.taskID = taskCounter++;
            cin.ignore(); // clear input buffer
            cout << "Enter substation name: ";
            getline(cin, task.substationName);
            cout << "Enter issue description: ";
            getline(cin, task.issue);
            outageQueue.enqueue(task);
        } else if (choice == 2) {
            OutageTask task = outageQueue.dequeue();
            if (task.taskID != -1) {
                cout << "Handling Task ID " << task.taskID
                     << " at substation " << task.substationName
                     << " - Issue: " << task.issue << endl;
            }
        } else if (choice == 3) {
            outageQueue.displayQueue();
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid option! Try again.\n";
        }
    }

    return 0;
}
