CC=g++
CPPFLAGS=-std=c++11 -c -Wall -DINCLUDED_SRC

all: workflow-build workflow

workflow-build: user server server/main.o server/PA_generator.o server/PA_verifier_server.o server/PB_verifier_server.o user/PA_to_PB_EasyReduction.o user/PA_to_PB_HardReduction.o user/PA_verifier.o user/PB_verifier.o
	$(CC) server/main.o server/PA_generator.o server/PA_verifier_server.o server/PB_verifier_server.o user/PA_to_PB_EasyReduction.o user/PA_to_PB_HardReduction.o user/PA_verifier.o user/PB_verifier.o -o workflow

server: server/main.cpp server/PA_generator.cpp server/PA_verifier_server.cpp server/PB_verifier_server.cpp
	$(CC) $(CPPFLAGS) user/main.cpp user/main.o
	$(CC) $(CPPFLAGS) user/PA_generator.cpp user/PA_generator.o
	$(CC) $(CPPFLAGS) user/PA_verifier_server.cpp user/PA_verifier_server.o
	$(CC) $(CPPFLAGS) user/PB_verifier_server.cpp user/PB_verifier_server.o

user: user/PA_to_PB_EasyReduction.cpp user/PA_to_PB_HardReduction.cpp user/PA_verifier.cpp user/PB_verifier.cpp
	$(CC) $(CPPFLAGS) user/PA_to_PB_EasyReduction.cpp user/PA_to_PB_EasyReduction.o
	$(CC) $(CPPFLAGS) user/PA_to_PB_HardReduction.cpp user/PA_to_PB_HardReduction.o
	$(CC) $(CPPFLAGS) user/PA_verifier.cpp user/PA_verifier.o
	$(CC) $(CPPFLAGS) user/PB_verifier.cpp user/PB_verifier.o

clean:
	rm workflow
	rm user/*.o
	rm server/*.o
