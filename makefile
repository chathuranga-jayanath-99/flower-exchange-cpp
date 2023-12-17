goinside: 
	cd ./src/

trader: Trader.o 
	g++ Trader.o -o trader 

Trader.o: ./src/Trader.cpp
	g++ -c ./src/Trader.cpp 

exchanger: Order.o Heap.o OrderBook.o OrderEntry.o Utils.o ExchangeApplication.o 
	g++ Order.o Heap.o OrderBook.o OrderEntry.o Utils.o ExchangeApplication.o -o exchanger 

Order.o: ./src/Order.cpp 
	g++ -c ./src/Order.cpp 

OrderEntry.o: ./src/OrderEntry.cpp 
	g++ -c ./src/OrderEntry.cpp 

Utils.o: ./src/Utils.cpp 
	g++ -c ./src/Utils.cpp

Heap.o: ./src/Heap.cpp 
	g++ -c ./src/Heap.cpp 

OrderBook.o: ./src/OrderBook.cpp 
	g++ -c ./src/OrderBook.cpp

ExchangeApplication.o: ./src/ExchangeApplication.cpp 
	g++ -c ./src/ExchangeApplication.cpp

run: goinside trader exchanger
	gnome-terminal --tab --title="Exchange Application" --command="./exchanger" & 
	sleep 2
	gnome-terminal --tab --title="Trader Application" --command="./trader" &

clean:
	rm -rf *.o trader exchanger

