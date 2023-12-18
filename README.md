# Flower-exchange-cpp

The Flower exhange system supports basic processing of orders. This system contains two applications: Trader Application and Exchange Application. 
- Trader Application focuses on submitting buy or sell orders for flowers.
- Exchange application focuses on processing the incoming order against existing orders in the order book and do a new, full or partial execution. 

Trader Application will read orders from the input csv file in `inputs` directory. User can enter which file to be entered. Then Trader Application passes each order to the Exchange Application for processing. 

After processing Exchange Application will generate an Execution Report. These Execution Reports are writen to a .csv file. User can enter which file to be written. Output file will be stored in the `results` directory. Invalid orders will be rejected.


## Execution

* Due to a library used (arpa/inet) the current system will not work in Windows systems.

1. Add your csv to the input folder
2. Execute the command `make run` from root 
3. It will open 2 terminals. One for the Trader Application and another for the Exchange Application.
4. Go to Trader Application terminal and provide the input filename (File must be available in the `inputs` directory), you need to open. 
If the filename is `input.csv` enter `input`
5. Program execution will start. 
6. Upon finishing, the Exchange Application will ask for a filename to store results. Enter a suitable name. 
7. You can find the results in the `results` directory. 


## Implementation details

### Socket Programming
System is implemented using a socket to communicate between Trader Application and Exhange Application. The Exchange application starts first. It opens a port and waits for incoming connections. The trader application, upon startup connects to the port and sends data. Upon sending all the data, the trader closes the connection. <br />
In the current implementation, the exchange application also terminates after the connection is closed and all data is processed, instead of listening for connection again. This is done under the assumption that only on csv file is processed at once.

### Design Patterns
Both the Trader and ExchangeApplication class follows a singleton pattern, adhering to the fact that only one instantiation should happen.

### Multithreading
The exchange application spawns two threads in addition to the main thread: Receiver and processor
The receiver listens for incoming data from the port, obtains them and publish them to a shared buffer.
The processor waits until there is data available in the shared buffer and if there is, does all the subsequent processing.
The shared resource, the buffer is made thread safe using a lock and a condition variable.

Advantages:
- Processing orders does not need to wait until all orders are received.
- Incoming orders will not be lost in communication.


### Batch Processing
Due to the memory allocated in the receive buffer of the socket, there is a limitation to the amount of data receievable at once. <br />
Currently 32 * 1024 * sizeof(char) is allocated which can receive around 1000 orders at once. <br />
Therefore if the trader receives more than 1000 orders, it waits a certain amount of time (100ms) before sending data again.
This allows the receiver thread to publish received data to the shared buffer and clear the receive buffer.


### Object Oriented Programming
The application adheres to Object-Oriented Programming principles, where the system is structured based on classes, acting as the foundation for object creation. <br />
Classes used and their objectives
- Trader - Trader application
- ExchangeApplication - Exchange application
- Order - Models orders
- OrderBook - Stores orders in heaps and process incoming orders
- OrderEntry - Models entries in the execution report
- Heap - Stores orders in Minheap or Maxheap

### Data Structures
The Order book for each instrument often gets updated. In each order book, the buy side always wants to keep the highest price order on top and the sell side always wants to keep the lowest price order on top. To satisfy those conditions a heap data structure is used. A max heap is allocated for each order book to maintain the buy side and a min heap is allocated for each order book to maintain the sell side.


## Experimentation

- The system passes all 7 given input testcases. The results can be found in src/testresults
- We tested the system with `25,177` orders. The system generated 35,670 order entries in `2.642334` seconds.

 

