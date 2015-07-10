CC=g++

CPPFLAGS=-std=c++11 -c -Wall -DINCLUDED_SRC

USERMASKFLAGS=-Dmain -DPA_Generate -DPA_Verifier_Server -DPB_Verifier_Server

all: workflow-build workflow

workflow-build: user server
	$(CC) server/main.o server/PA_generator.o server/PA_verifier_server.o server/PB_verifier_server.o user/PA_to_PB_EasyReduction.o user/PA_to_PB_HardReduction.o user/PA_verifier.o user/PB_verifier.o -o workflow

server: server/main.o server/PA_generator.o server/PA_verifier_server.o server/PB_verifier_server.o

server/main.o: server/main.cpp
	$(CC) $(CPPFLAGS) server/main.cpp -o server/main.o

server/PA_generator.o: server/PA_generator.cpp
	$(CC) $(CPPFLAGS) server/PA_generator.cpp -o server/PA_generator.o

server/PA_verifier_server.o: server/PA_verifier_server.cpp
	$(CC) $(CPPFLAGS) server/PA_verifier_server.cpp -o server/PA_verifier_server.o

server/PB_verifier_server.o: server/PB_verifier_server.cpp
	$(CC) $(CPPFLAGS) server/PB_verifier_server.cpp -o server/PB_verifier_server.o

user: user/PA_to_PB_EasyReduction.o user/PA_to_PB_HardReduction.o user/PA_verifier.o user/PB_verifier.o

user/PA_to_PB_EasyReduction.o: user/PA_to_PB_EasyReduction.cpp
	$(CC) $(CPPFLAGS) $(USERMASKFLAGS) -DPA_Verifier -DPB_Verifier -DReductionHard_FromPA_ToPB user/PA_to_PB_EasyReduction.cpp -o user/PA_to_PB_EasyReduction.o

user/PA_to_PB_HardReduction.o: user/PA_to_PB_HardReduction.cpp
	$(CC) $(CPPFLAGS) $(USERMASKFLAGS) -DPA_Verifier -DPB_Verifier -DReductionEasy_FromPA_ToPB user/PA_to_PB_HardReduction.cpp -o user/PA_to_PB_HardReduction.o

user/PA_verifier.o: user/PA_verifier.cpp
	$(CC) $(CPPFLAGS) $(USERMASKFLAGS) -DPB_Verifier -DReductionEasy_FromPA_ToPB -DReductionHard_FromPA_ToPB user/PA_verifier.cpp -o user/PA_verifier.o

user/PB_verifier.o: user/PB_verifier.cpp
	$(CC) $(CPPFLAGS) $(USERMASKFLAGS) -DPA_Verifier -DReductionEasy_FromPA_ToPB -DReductionHard_FromPA_ToPB user/PB_verifier.cpp -o user/PB_verifier.o

clean:
	rm server/*.o
	rm user/*.o
	rm workflow
