
#include <iostream>
#include <set>
#include "../set.cpp"

int main(void) {

    int n;
    n = 1000000;
    Set<int> st;
    for (int i = 0; i < n; i++) {
        st.insert(i);
    }
    for (int i = 0; i < 2 * n; i++) {
        st.find(i);
    }
    std::cerr << st.size() << std::endl;
}
