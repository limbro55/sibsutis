CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SERVER = server
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): server.cpp
	$(CXX) $(CXXFLAGS) server.cpp -o $(SERVER)

$(CLIENT): client.cpp
	$(CXX) $(CXXFLAGS) client.cpp -o $(CLIENT)

clean:
	rm -f $(SERVER) $(CLIENT)

re: clean all

.PHONY: all clean re