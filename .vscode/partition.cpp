
#include <iostream>
#include <vector>
using namespace std;


int partition(vector<int>& a, int b, int e) {
    int part_val = a[b];

    int part_index = b;
    for (int i = b+1; i < e; ++i) {
        if (a[i] < part_val) {
            swap(a[i], a[++part_index]);
        }
    }

    swap(a[b], a[part_index]);
    return part_index;
}

void quick_sort(vector<int>& a, int b, int e) {
    if (b < e) {
        int m = partition(a, b, e);
        quick_sort(a, b, m);
        quick_sort(a, m+1, e);
    }
}

int main() {

    vector<int> a  = {4, 3 ,5 ,6 ,3, 2, 6, 2, 4, 6, 1, 11};

    copy(a.cbegin(), a.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;

    quick_sort(a, 0, a.size()/2);

    copy(a.cbegin(), a.cend(), ostream_iterator<int>(cout, " "));
    cout << endl;
}