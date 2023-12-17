SRCS1 = Trader.cpp 
SRCS2 = Order.cpp Heap.cpp  OrderBook.cpp OrderEntry.cpp Utils.cpp ExchangeApplication.cpp

trader: Trader.o 
	g++ Trader.o -o trader 

Trader.o: Trader.cpp 
	g++ -c Trader.cpp 

exchanger: Order.o Heap.o OrderBook.o OrderEntry.o Utils.o ExchangeApplication.o 
	g++ Order.o Heap.o OrderBook.o OrderEntry.o Utils.o ExchangeApplication.o -o exchanger 

Order.o: Order.cpp 
	g++ -c Order.cpp 

OrderEntry.o: OrderEntry.cpp 
	g++ -c OrderEntry.cpp 

Utils.o: Utils.cpp 
	g++ -c Utils.cpp

Heap.o: Heap.cpp 
	g++ -c Heap.cpp 

OrderBook.o: OrderBook.cpp 
	g++ -c OrderBook.cpp

ExchangeApplication.o: ExchangeApplication.cpp 
	g++ -c ExchangeApplication.cpp

run: trader exchanger
	gnome-terminal --tab --title="Exchange Application" --command="./exchanger" & 
	sleep 2
	gnome-terminal --tab --title="Trader Application" --command="./trader" &

clean:
	rm -rf *.o trader exchanger

