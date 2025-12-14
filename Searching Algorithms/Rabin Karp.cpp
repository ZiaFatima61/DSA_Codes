#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Rabin-Karp function to detect patterns in logs
void rabinKarpLogs(const vector<string>& logs, const string& pattern, int d, int q) {
    int m = pattern.size();
    int h = 1;

    // Precompute h = d^(m-1) % q
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    int p = 0; // Hash value for pattern

    // Compute hash of the pattern
    for (int i = 0; i < m; i++)
        p = (d * p + pattern[i]) % q;

    // Scan each log entry
    for (int logIndex = 0; logIndex < logs.size(); logIndex++) {
        const string& text = logs[logIndex];
        int n = text.size();
        int t = 0; // Hash for text window

        // Initial hash for the first window
        for (int i = 0; i < m && i < n; i++)
            t = (d * t + text[i]) % q;

        // Slide over the text
        for (int s = 0; s <= n - m; s++) {
            if (p == t) {
                bool match = true;
                for (int i = 0; i < m; i++) {
                    if (text[s + i] != pattern[i]) {
                        match = false;
                        break;
                    }
                }
                if (match)
                    cout << "Pattern found in log " << logIndex + 1 
                         << " at position " << s << endl;
            }

            if (s < n - m) {
                t = (d * (t - text[s] * h) + text[s + m]) % q;
                if (t < 0)
                    t += q;
            }
        }
    }
}

int main() {
    // Example tourism logs
    vector<string> travelLogs = {
        "BookingID123: UserX booked HotelABC",
        "BookingID124: UserY booked HotelXYZ",
        "BookingID125: UserX booked HotelABC",
        "BookingID126: UserZ booked HotelABC"
    };

    string suspiciousPattern;
    cout << "Enter pattern to search for in travel logs: ";
    getline(cin, suspiciousPattern);

    int d = 256;     // Number of characters in ASCII
    int q = 101;     // A prime number for hashing

    rabinKarpLogs(travelLogs, suspiciousPattern, d, q);

    return 0;
}
