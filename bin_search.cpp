#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


int main() {

    vector<int> a = {2, 5, 7, 8, 4, 3, 2, 1, 6, 0};
    sort(a.begin(), a.end());

    int value = -4;
    int res = -1;

    int b = 0, e = a.size();
    while (b <= e) {
        int m = b + (e - b) / 2;

        if (a[m] == value) {
            res = m;
            break;
        }

        if (a[m] < value)
            b = m + 1;
        else
            e = m - 1;
    }

    cout << "Index = " << res << endl;

    copy(a.cbegin(), a.cend(), ostream_iterator<int>(cout, " "));
}