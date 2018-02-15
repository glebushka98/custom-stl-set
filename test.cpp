#include <catch.hpp>

#include <string>
#include <vector>
#include <random>
#include <memory>
#include <set.cpp>
#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
using std::vector;

using std::random_shuffle;


TEST_CASE("Splay tests") {
    {
        SplayTree<int> tree;
        tree.Insert(10);
        REQUIRE(tree.Find(10));
        tree._Debug_Linked();
    }

    {
        SplayTree<int> tree;

        tree.Insert(1);
        tree.Insert(1);
        REQUIRE(tree.Size() == 1);
    }

    {
        SplayTree<int> tree;

        tree.Insert(1);
        tree.Insert(2);
        REQUIRE(tree.Size() == 2);
    }

    {
        SplayTree<int> tree;

        tree.Insert(3);
        tree.Insert(1);
        tree.Insert(2);
        tree.Insert(2);
        tree.Delete(2);
        REQUIRE(tree.Size() == 2);
    }

    {
        SplayTree<int> tree;
        vector<int> v{1, 2, 3, 4, 5, 6, 1};
        srand(228);
        for (int i : v) {
            tree.Insert(i);
            tree._Debug_Validate();
        }
        tree._Debug_Validate();

        REQUIRE(tree.Size() == 6);
        random_shuffle(v.begin(), v.end());
        for (int i : v) {
            tree.Delete(i);
            tree._Debug_Validate();
        }
        REQUIRE(tree.Size() == 0);
    }

    {
        SplayTree<int> tree;
        vector<int> v;
        srand(228);
        for (int i = 0; i < 10000; i++) {
            v.push_back(i);
        }
        random_shuffle(v.begin(), v.end());

        for (int i : v) {
            tree.Insert(i);
        }

        REQUIRE(tree.Size() == 10000);
        random_shuffle(v.begin(), v.end());
        for (int i : v) {
            tree.Delete(i);
        }
        REQUIRE(tree.Size() == 0);
    }

    {
        SplayTree<int> tree;
        for (int i = 0; i < 100; i++) {
            tree.Insert(i);
        }
        tree._Debug_Linked();

        for (int i = 99; i >= 0; i--) {
            REQUIRE(tree.Find(i));
            tree.Delete(i);
            REQUIRE(!tree.Find(i));
            REQUIRE(tree.Size() == i);
        }
        REQUIRE(tree.Size() == 0);
    }


}

TEST_CASE("Deep tests") {
    {
        int n = 100;
        SplayTree<int> tree;
        vector<int> v;
        for (int i = 0; i < n; i++) {
            v.push_back(i);
        }
        random_shuffle(v.begin(), v.end());
        for (int i : v) {
            tree.Insert(i);
        }
        v.resize(n / 2);
        random_shuffle(v.begin(), v.end());
        for (int i : v) {
            tree.Delete(i);
        }

        tree._Debug_Linked();
        auto deep_copy = tree.GetDeepCopy();
        deep_copy._Debug_Validate();

        deep_copy._Debug_Linked();
        tree._Debug_Linked();
        REQUIRE(deep_copy.Size() == n / 2);
        REQUIRE(tree.Size() == n / 2);

    }
}

TEST_CASE("Set tests") {
    {
        Set<int> st;
        for (int i : {3, 4, 6, 1, 2}) {
            st.insert(i);
        }
        REQUIRE(st.size() == 5);
        st.erase(4);
        REQUIRE(st.size() == 4);

        vector<int> v;
        for (auto el : st) {
            v.push_back(el);
        }
        REQUIRE(st.size() == v.size());
        REQUIRE(st.size() == 4);
        REQUIRE(v[0] == 1);
        REQUIRE(v[1] == 2);
        REQUIRE(v[2] == 3);
        REQUIRE(v[3] == 6);
    }

    {
        Set<int> st;

        srand(228);
        for (int i = 0; i < 1000; i++) {
            st.insert(1000 - i);
        }

        for (int i = 1; i <= 1000; i++) {
            REQUIRE(st.find(i) != st.end());
            REQUIRE((*st.find(i)) == i);
        }

        for (int i = 0; i < 1000; i++) {
            REQUIRE(*st.lower_bound(1000 - i) == 1000 - i);
        }

        REQUIRE(*st.lower_bound(-1) == 1);
        REQUIRE(st.lower_bound(1001) == st.end());



    }
}



