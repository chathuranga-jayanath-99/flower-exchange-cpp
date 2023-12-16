# flower-exchange-cpp

Flower exhange system supports basic trading. This system contains two applications: Trader Application and Exchange Application. 
- Trader Application focuses on submitting buy or sell orders for flowers.
- Exchange application focuses on incodimg order against existing order in the order book and do a full or partial execution. 

System is implemented using a socket to communicate between Trader Application and Exhange Application. Trader Application will read orders from a .csv which contains orders. Then it passes each order to the Exchange Application for processing. After processing Exchange Application will generate Execution Report. These Execution Reports are writen to a .csv file. 

## Execute

Executing following commandd will start the execution of the program. 
