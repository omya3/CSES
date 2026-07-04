#include <iostream>
#include <vector>

using namespace std;

// Element structure to store the raw value alongside the accumulated OR sum
struct StackElement {
    int value;
    int current_or;
};

// 1. THE AGGREGATION STACK LOGIC
struct AggStack {
    vector<StackElement> st;

    bool empty() {
        return st.empty();
    }

    void push(int val) {
        int new_or = val;
        if (!st.empty()) {
            new_or |= st.back().current_or; // Accumulate OR with the element below it
        }
        st.push_back({val, new_or});
    }

    void pop() {
        if (!st.empty()) {
            st.pop_back();
        }
    }

    StackElement top() {
        return st.back();
    }
    
    int get_or() {
        if (st.empty()) return 0;
        return st.back().current_or;
    }
};

// 2. THE AGGREGATION QUEUE (SWAG) LOGIC
struct AggQueue {
    AggStack front_stack; // Handles popping from the front
    AggStack back_stack;  // Handles pushing to the back

    void push(int val) {
        back_stack.push(val);
    }

    void pop() {
        // If the front stack is empty, transfer everything from back to front
        if (front_stack.empty()) {
            while (!back_stack.empty()) {
                front_stack.push(back_stack.top().value);
                back_stack.pop();
            }
        }
        front_stack.pop();
    }

    int get_window_or() {
        // Total window OR is the combined OR sum of both stacks
        return front_stack.get_or() | back_stack.get_or();
    }
};

int main()
{
    // Optimise standard I/O streams for competitive programming speed
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long n, k;
    if (!(cin >> n >> k))
        return 0;

    long long x, a, b, c;
    cin >> x >> a >> b >> c;

    AggQueue q;
    long long ans = 0;
    long long current_x = x;

    // Process all elements sequentially
    for (int i = 0; i < n; i++)
    {
        if (i > 0) {
            current_x = ((__int128)current_x * a + b) % c; // Prevent 64-bit overflow
        }

        // Add current element to the aggregation queue
        q.push(current_x);

        // Once the queue exceeds size k, pop the oldest element out from the front
        if (i >= k) {
            q.pop();
        }

        // Once the first full window of size k is completely formed
        if (i >= k - 1) {
            ans ^= q.get_window_or();
        }
    }

    cout << ans << "\n";
    return 0;
}
