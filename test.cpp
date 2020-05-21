//
// Created by sobral on 27/07/19.
//
#include <limits.h>
#include <time.h>
#include <string>
#include <algorithm>
#include <vector>
#include <ostream>
#include <sstream>
#include <fstream>
#include <list>
#include <random>
#include "questao.h"
#include "gtest/gtest.h"

using namespace std;

const char SEP[] = ",.;:/|-&%$+=*?";
const char VOGAIS[] = "aeiouy";
const char CONS[] = "bcdfghjklmnpqrstvwxz";

class TesteQuestao: public ::testing::Test {
protected:
    virtual void SetUp() {
        srand(clock());
    }

    string gen_word(int N, int mins=0) {
        string s;
        int n;
        bool vogal = rand() % 2;

        n = mins + (rand() % N);
        while (n-- > 0) {
            if (vogal) s += VOGAIS[rand()%(sizeof(VOGAIS)-1)];
            else s+= CONS[rand()%(sizeof(CONS)-1)];
            vogal = not vogal;
        }
        return s;
    }

    list<string> gen_list(int N) {
        list<string> r;

        return gen_list(N, r);
    }

    list<string> gen_list(int N, const list<string> & l) {
        list<string> r;

        while (N-- > 0) {
            auto w = gen_word(3,4);

            if (find(l.begin(), l.end(), w) == l.end()) r.push_back(w);
        }
        return r;
    }

    string mostra(const list<string> & l, char sep=' ') {
        if (l.empty()) return "";

        ostringstream out;

        for (auto & x: l) out << x << sep;
        string res = out.str();
        res.pop_back();
        return res;
    }

    void info(const string & header, const list<string> & r, const list<string> & l1, const list<string> & l2) {
        FAIL() << header << ": "
               << mostra(r, ',') << endl
               << "Lista 1: " << mostra(l1, ',') << endl
               << "Lista 2: " << mostra(l2, ',') << endl;
    }

    void test_vazia(list<string> & l1, list<string> & l2) {
        try {
            auto r = interseccao(l1, l2);

            if (r.size() > 0) {
                info("interseccao deveria ser um conjunto vazio, mas retornou isto", r, l1, l2);
                return;
            }

        } catch (...) {
            FAIL() << "ocorreu uma exceção";
        }
    }

    void embaralha(list<string> & l) {
        vector<string> v(l.begin(), l.end());

        shuffle(v.begin(), v.end(), std::default_random_engine(1));

        l.clear();
        for (auto & x: v) l.push_back(x);

    }
};

TEST_F(TesteQuestao, Vazia)
{
    list<string> l1, l2;

    // ambas vazias
    test_vazia(l1, l2);

    //l2 vazia
    l1=gen_list(5);
    test_vazia(l1, l2);

    // l1 vazia
    l1.clear();
    l2=gen_list(5);
    test_vazia(l1, l2);

    // l1 e l2 sem valores em comum
    l1 = gen_list(5, l2);
    test_vazia(l1, l2);
}

TEST_F(TesteQuestao, Iguais)
{
    try {
        list<string> l1, l2;

        l1 = gen_list(8);
        l2 = l1;
        auto r = interseccao(l1, l2);
        l1.sort();
        r.sort();

        if (r != l1) {
            info("interseccao deveria ser idêntica às listas, mas retornou isto", r, l1, l2);
            return;
        }

    } catch (...) {
        FAIL() << "ocorreu uma exceção";
    }
}

TEST_F(TesteQuestao, Repetidos)
{
    try {
        list<string> l1, l2;

        l2 = gen_list(8);
        l1 = l2;
//        l1.pop_back();
//        l1.pop_back();
        l1.push_back(l1.front());
        l1.push_back(l1.front());
        embaralha(l1);

        auto r = interseccao(l1, l2);
        l2.sort();
        r.sort();

        if (r != l2) {
            info("interseccao deveria ser: " + mostra(l2, ',')+" ... mas retornou isto", r, l1, l2);
            return;
        }

        r = interseccao(l2, l1);
        l2.sort();
        r.sort();

        if (r != l2) {
            info("interseccao deveria ser: " + mostra(l2, ',')+" ... mas retornou isto", r, l2, l1);
            return;
        }

    } catch (...) {
        FAIL() << "ocorreu uma exceção";
    }
}

TEST_F(TesteQuestao, Normal) {
    string sep;
    list<string> q;

    try {
        for (int n=0; n < 10; n++) {
            list<string> l1, l2, l3, l4, lr;

            l2 = gen_list(8);
            l1 = l2;
            l3 = gen_list(3);
            l4 = gen_list(3);
            lr = l1;
            lr.sort();

            l1.insert(l1.begin(), l3.begin(), l3.end());
            embaralha(l1);
            l2.insert(l2.begin(), l4.begin(), l4.end());
            embaralha(l2);

            auto r = interseccao(l1, l2);

            r.sort();

            if (lr != r) {
                info("1 interseccao deveria ser: " + mostra(lr, ',')+" ... mas retornou isto", r, l1, l2);
                return;
            }

            r = interseccao(l2, l1);

            r.sort();

            if (lr != r) {
                info("interseccao deveria ser: " + mostra(lr, ',')+" ... mas retornou isto", r, l2, l1);
                return;
            }
        }
    } catch (...) {
        FAIL() << "ocorreu uma exceção";
    }
}

