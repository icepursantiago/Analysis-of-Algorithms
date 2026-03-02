#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>
using namespace std;

struct rod{
    char name;
    int disks[64];
    int top = -1;
};

void push(rod &Rod, int disk){
    Rod.disks[++Rod.top] = disk;
}

int pop(rod &Rod){
    int disk = Rod.disks[Rod.top];
    Rod.top--;
    return disk;
}

int peek(rod &Rod){
    return Rod.disks[Rod.top];
}

void push_disk(rod &from_rod, rod &to_rod, bool silent = false){
    if(from_rod.top < 0) return;
    if(to_rod.top >= 0 && peek(from_rod) > peek(to_rod)) return;

    int disk = pop(from_rod);
    push(to_rod, disk);

    if(!silent){
        cout << "Move disk " << disk
             << " from rod " << from_rod.name
             << " to rod " << to_rod.name << endl;
    }
}

void move_between(rod &rod1, rod &rod2, bool silent = false){
    if(rod1.top < 0) push_disk(rod2, rod1, silent);
    else if(rod2.top < 0) push_disk(rod1, rod2, silent);
    else if(peek(rod1) < peek(rod2)) push_disk(rod1, rod2, silent);
    else push_disk(rod2, rod1, silent);
}

void hanoi(int n, bool silent = false){
    rod rodA, rodB, rodC;
    rodA.name = 'A';
    rodB.name = 'B';
    rodC.name = 'C';

    for(int i = n; i >= 1; --i){
        push(rodA, i);
    }

    int total_moves = (1 << n) - 1;

    for(int move = 1; move <= total_moves; ++move){
        if(n % 2 == 1){
            if(move % 3 == 1) move_between(rodA, rodC, silent);
            else if(move % 3 == 2) move_between(rodA, rodB, silent);
            else move_between(rodB, rodC, silent);
        }else{
            if(move % 3 == 1) move_between(rodA, rodB, silent);
            else if(move % 3 == 2) move_between(rodA, rodC, silent);
            else move_between(rodB, rodC, silent);
        }
    }
}

void hanoi_recursive(int n, rod &from_rod, rod &to_rod, rod &aux_rod, bool silent = false){
    if(n == 1){
        push_disk(from_rod, to_rod, silent);
        return;
    }
    hanoi_recursive(n-1, from_rod, aux_rod, to_rod, silent);
    push_disk(from_rod, to_rod, silent);
    hanoi_recursive(n-1, aux_rod, to_rod, from_rod, silent);
}

void empirical_analysis(){
    ofstream file("hanoi_analysis.csv");
    file << "n,Theoretical_Moves,Iterative_Time_ms,Recursive_Time_ms\n";

    cout << "\n=== EMPIRICAL ANALYSIS ===\n";
    cout << "Running tests from n=1 to n=25...\n\n";
    cout << "n\tTheoretical\tIterative(ms)\tRecursive(ms)\n";
    cout << "-----------------------------------------------------------\n";

    for(int n = 1; n <= 25; ++n){
        long long theoretical_moves = (1LL << n) - 1;

        // Test iterative algorithm
        auto t_start = chrono::high_resolution_clock::now();
        hanoi(n, true);
        auto t_finish = chrono::high_resolution_clock::now();
        double iterative_time = chrono::duration<double, milli>(t_finish - t_start).count();

        // Test recursive algorithm
        rod rodA, rodB, rodC;
        rodA.name = 'A';
        rodB.name = 'B';
        rodC.name = 'C';
        for(int i = n; i >= 1; --i){
            push(rodA, i);
        }

        t_start = chrono::high_resolution_clock::now();
        hanoi_recursive(n, rodA, rodC, rodB, true);
        t_finish = chrono::high_resolution_clock::now();
        double recursive_time = chrono::duration<double, milli>(t_finish - t_start).count();

        // Display results
        cout << n << "\t" << theoretical_moves << "\t\t" 
             << iterative_time << "\t\t" << recursive_time << endl;

        // Save to CSV
        file << n << "," << theoretical_moves << "," 
             << iterative_time << "," << recursive_time << "\n";
    }

    file.close();

}

int main(){
    int choice;
    cout << "=== TOWERS OF HANOI ===\n";
    cout << "1. Demo (show moves)\n";
    cout << "2. Empirical Analysis (timing)\n";
    cout << "Choose option: ";
    cin >> choice;

    if(choice == 1){
        int n;
        cout << "Enter number of disks: ";
        cin >> n;

        if(n < 1 || n > 30){
            cout << "Enter 1..30" << endl;
            return 1;
        }

        cout << "\n=== ITERATIVE SOLUTION ===\n";
        hanoi(n);
        
        cout << "\n=== RECURSIVE SOLUTION ===\n";
        rod rodA, rodB, rodC;
        rodA.name = 'A';
        rodB.name = 'B';
        rodC.name = 'C';
        for(int i = n; i >= 1; --i){
            push(rodA, i);
        }
        hanoi_recursive(n, rodA, rodC, rodB);
        
    } else if(choice == 2){
        empirical_analysis();
    } else {
        cout << "Invalid choice\n";
        return 1;
    }

    return 0;
}
