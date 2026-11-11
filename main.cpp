// EECS 348 - Lab 11: Debugging and Testing
// Author: Nathaniel Lanter
//
// Faulty function under test + a correct reference implementation.
// Each test prints the attendance record, expected/actual absence count,
// and expected/actual output (true = student fails the course).

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Function under test (contains the FAULT).
// absent_count is split out only so the test driver can observe the
// internal state; the logic is identical to Algorithm 1 in the handout.
// ---------------------------------------------------------------------------
int absent_count_faulty(const vector<int>& attendance_records) {
    int absent_count = 0;
    // FAULT: loop starts at i = 1, so lecture 0 (the first lecture) is never
    // checked. Correct code is: for (int i = 0; ...)
    for (int i = 1; i < (int)attendance_records.size(); ++i) {
        absent_count += attendance_records[i] == 0;
    }
    return absent_count;
}

bool fail_lecture(const vector<int>& attendance_records) {
    return absent_count_faulty(attendance_records) >= 3;
}

// ---------------------------------------------------------------------------
// Correct reference (used to compute the EXPECTED values).
// ---------------------------------------------------------------------------
int absent_count_expected(const vector<int>& attendance_records) {
    int absent_count = 0;
    for (int i = 0; i < (int)attendance_records.size(); ++i) {
        absent_count += attendance_records[i] == 0;
    }
    return absent_count;
}

bool fail_expected(const vector<int>& attendance_records) {
    return absent_count_expected(attendance_records) >= 3;
}

// ---------------------------------------------------------------------------
// Test driver
// ---------------------------------------------------------------------------
static string record_str(const vector<int>& r) {
    string s = "[";
    for (size_t i = 0; i < r.size(); ++i) {
        s += to_string(r[i]);
        if (i + 1 < r.size()) s += ", ";
    }
    return s + "]";
}

static void run_test(const string& name, const vector<int>& r) {
    int exp_count = absent_count_expected(r);
    int act_count = absent_count_faulty(r);
    bool exp_out = fail_expected(r);
    bool act_out = fail_lecture(r);

    bool error_state = (exp_count != act_count);
    bool failure = (exp_out != act_out);

    cout << "=== " << name << " ===\n";
    cout << "Attendance record : " << record_str(r) << "\n";
    cout << "Absence count     : expected " << exp_count << ", actual " << act_count << "\n";
    cout << "Output (fails?)   : expected " << (exp_out ? "true" : "false")
         << ", actual " << (act_out ? "true" : "false") << "\n";
    cout << "Fault executed    : yes (the loop initialisation runs on every call)\n";
    cout << "Error state       : " << (error_state ? "yes" : "no") << "\n";
    cout << "Failure           : " << (failure ? "yes" : "no") << "\n\n";
}

int main() {
    // Q2: impossible. The faulty statement `int i = 1` is the loop
    // initialisation, which executes on every call, whatever the input.
    cout << "Q2: No test case can avoid executing the fault (see ANSWERS.md).\n\n";

    // Q3: fault executed, no error state: skipped lecture 0 was a present (1).
    run_test("Q3: fault executed, no error state",
             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1});

    // Q4: error state, no failure: lecture 0 absent so the count is off by
    // one (4 vs 3), but both counts are >= 3 so the output is still correct.
    run_test("Q4: error state, no failure",
             {0, 0, 0, 0, 1, 1, 1, 1, 1, 1});

    // Q5: failure: lecture 0 absent pushes the true count to exactly 3, but
    // the faulty code sees 2, so it wrongly reports that the student passes.
    run_test("Q5: failure",
             {0, 0, 0, 1, 1, 1, 1, 1, 1, 1});

    return 0;
}
