#include <iostream>
#include <limits>

using namespace std;

static void swapArithmetic(long long &u, long long &v) {
    // Swap without extra storage using arithmetic.
    // Note: may overflow if u+v exceeds range of the type.
    u = u + v;
    v = u - v;
    u = u - v;
}

static void swapXor(int &u, int &v) {
    // Swap without extra storage using XOR (integers only).
    u = u ^ v;
    v = u ^ v;
    u = u ^ v;
}

int main() {
    cout << "=== Problem 1: Swap without extra storage ===\n\n";

    {
        long long u = 25, v = -13;
        cout << "[Arithmetic swap]\n";
        cout << "Before: u=" << u << ", v=" << v << "\n";
        swapArithmetic(u, v);
        cout << "After : u=" << u << ", v=" << v << "\n\n";
    }

    {
        int u = 42, v = 99;
        cout << "[XOR swap]\n";
        cout << "Before: u=" << u << ", v=" << v << "\n";
        swapXor(u, v);
        cout << "After : u=" << u << ", v=" << v << "\n\n";
    }

    cout << "Note: Arithmetic swap can overflow; XOR swap is limited to integers.\n";
    return 0;
}
