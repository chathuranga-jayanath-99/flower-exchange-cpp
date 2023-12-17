# Flower-exchange-cpp

The Flower exhange system supports basic processing of orders. This system contains two applications: Trader Application and Exchange Application. 
- Trader Application focuses on submitting buy or sell orders for flowers.
- Exchange application focuses on processing the incoming order against existing orders in the order book and do a new, full or partial execution. 

Trader Application will read orders from the input csv file in `inputs` directory. User can enter which file to be entered. Then Trader Application passes each order to the Exchange Application for processing. 

After processing Exchange Application will generate an Execution Report. These Execution Reports are writen to a .csv file. User can enter which file to be written. Output file will be stored in the `results` directory. 


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

System is implemented using a socket to communicate between Trader Application and Exhange Application. Exchange application starts first. It opens a port and waits for incoming connections. The trader application, upon startup connects to the port and sends data.

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


## Experimentation

- The system passes all 7 given input testcases. The results can be found in src/testresults
- We tested the system with 25,177 orders. The system generated 35,670 order entries in [] seconds.

 

