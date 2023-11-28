// banker_algorithm.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Define the maximum number of processes and resources
const int MAX_PROCESSES = 5;
const int MAX_RESOURCES = 3;

// Data structure to represent the state of the system
struct SystemState {
    int available[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
};

// Function to read the initial system state from the input file
void readInput(const char* filename, SystemState& state) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cerr << "Error opening the input file." << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_PROCESSES; ++i) {
        inputFile >> state.max[i][0] >> state.max[i][1] >> state.max[i][2];
        inputFile >> state.allocation[i][0] >> state.allocation[i][1] >> state.allocation[i][2];
        state.need[i][0] = state.max[i][0] - state.allocation[i][0];
        state.need[i][1] = state.max[i][1] - state.allocation[i][1];
        state.need[i][2] = state.max[i][2] - state.allocation[i][2];
    }

    for (int j = 0; j < MAX_RESOURCES; ++j) {
        inputFile >> state.available[j];
    }

    inputFile.close();
}

// Function to check if the system is in a safe state
bool isSafeState(const SystemState& state, vector<int>& safeSequence) {
    vector<int> work(state.available, state.available + MAX_RESOURCES);
    vector<bool> finish(MAX_PROCESSES, false);

    for (int i = 0; i < MAX_PROCESSES; ++i) {
        if (!finish[i] && 
            state.need[i][0] <= work[0] &&
            state.need[i][1] <= work[1] &&
            state.need[i][2] <= work[2]) {

            // Simulate resource allocation
            work[0] += state.allocation[i][0];
            work[1] += state.allocation[i][1];
            work[2] += state.allocation[i][2];
            finish[i] = true;
            safeSequence.push_back(i);

            // Reset to check from the beginning
            i = -1;
        }
    }

    // Check if all processes are finished
    return all_of(finish.begin(), finish.end(), [](bool val) { return val; });
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return EXIT_FAILURE;
    }

    const char* filename = argv[1];

    SystemState state;
    readInput(filename, state);

    vector<int> safeSequence;

    if (isSafeState(state, safeSequence)) {
        cout << "System is in a safe state." << endl;
        cout << "Safe Sequence: ";
        for (int i = 0; i < safeSequence.size(); ++i) {
            cout << "P" << safeSequence[i];
            if (i != safeSequence.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        cout << "System is NOT in a safe state." << endl;
    }

    return 0;
}

