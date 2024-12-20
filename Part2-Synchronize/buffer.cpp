#include <windows.h>
#include <iostream>
#include <vector>
#include <stdlib.h>

typedef int buffer_item;

class Buffer {
    private:
        #define BUFFER_SIZE 5
        std::vector<buffer_item> buffer;

    public:
        HANDLE mutex;
        HANDLE empty;
        HANDLE full;

        Buffer() {
            mutex = CreateMutex(NULL, FALSE, NULL);
            empty = CreateSemaphore(NULL, 5, BUFFER_SIZE, NULL);
            full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
        }

        int insert_item(buffer_item item) {
            if (buffer.size() < BUFFER_SIZE) {
                buffer.push_back(item);     // insert item into buffer
                return 0;                   // return 0 if successful
            }
            else {
                return -1;                  // return -1 if error
            }
        }

        int remove_item(buffer_item &item) {
            if (buffer.size() > 0) {
                item = buffer.back();       // set item equal to the value at the back of the buffer
                buffer.pop_back();          // remove item from buffer
                return 0;                   // return 0 if successful
            }
            else {
                item = -1;                  // set item = -1 if error
                return -1;                  // return -1 if error
            }
        }

        /* display buffer */
        void display() {
            std::cout << "[ ";
            for (int i = 0; i < buffer.size(); i++) {
                std::cout << buffer[i] << " ";
            }
            std::cout << "]" << std::endl;
        }
};