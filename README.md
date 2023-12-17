# flower-exchange-cpp

Flower exhange system supports basic trading. This system contains two applications: Trader Application and Exchange Application. 
- Trader Application focuses on submitting buy or sell orders for flowers.
- Exchange application focuses on incodimg order against existing order in the order book and do a full or partial execution. 

System is implemented using a socket to communicate between Trader Application and Exhange Application. Trader Application will read orders in `inputs` directory. User can enter which file to be entered. Then Trader Application passes each order to the Exchange Application for processing. After processing Exchange Application will generate Execution Report. These Execution Reports are writen to a .csv file. User can enter which file to be written. Output file will be stored in the `results` directory. 

## Execute

2. Execute the command `make run`. 
3. It will open 2 terminals one for Trader Application and another for Exchange Application. 
4. Go to Trader Application and provide the input filename (file must be available in the `inputs` directory), you need to open.
5. The it will start sending data to Exchange Application. 
6. Then provide an output filename in Exchange Application to store results. 
7. Then you can find the results in the `results` directory.  

