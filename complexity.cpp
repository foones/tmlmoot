#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

std::string file_contents(const std::string& filename) {
    std::ifstream ifs(filename);
    return std::string((std::istreambuf_iterator<char>(ifs)),
                       (std::istreambuf_iterator<char>()));
}

typedef unsigned long long int u64;
typedef std::pair<u64, u64> u64pair;

void swap(u64& x, u64& y) {
    u64 tmp = x;
    x = y;
    y = tmp;
}

u64pair value(size_t n, u64* p, size_t t, size_t i) {
    return u64pair(p[i], p[(i + t) % n]);
}

size_t randrange(size_t i, size_t j) {
    double r = random() / ((double)RAND_MAX + 1);
    return floor(i + r * (j - i));
}

void qsort(size_t n, u64* r, u64* p, size_t t, size_t l, size_t u) {
    if (l + 1 < u) {
        swap(r[l], r[randrange(l, u)]);
        u64pair pivot = value(n, p, t, r[l]);
        size_t i = l + 1;
        size_t j = u;
        while (i < j) {
            if (value(n, p, t, r[i]) <= pivot) {
                i++;
            } else {
                j--;
                swap(r[i], r[j]);
            }
        }

        swap(r[l], r[i - 1]);

        qsort(n, r, p, t, l, i - 1);
        qsort(n, r, p, t, i, u);
    }
}

void invert(int n, u64* r, u64* p) {
    for (int i = 0; i < n; i++) {
        p[r[i]] = i;
    }
}

void suffix_array(size_t n, const std::string& s, u64* r, u64* p) {
    for (size_t i = 0; i < n; i++) {
        p[i] = (u64)s[i];
    }

    for (size_t i = 0; i < n; i++) {
        r[i] = i;
    }

    for (size_t t = 1; t < n; t *= 2) {
        qsort(n, r, p, t, 0, n);
        invert(n, r, p);
    }
}

void lcp(size_t n, const std::string& s, u64* r, u64* p, u64* h) {
    size_t hv = 0; 
    for (size_t i = 0; i < n; i++) {
        if (p[i] == n - 1) {
            hv = 0;
            continue;
        }
        size_t j = r[p[i] + 1];
        while (hv < n && s[(i + hv) % n] == s[(j + hv) % n]) {
            hv++;
        }
        h[p[i]] = hv;
        if (hv > 0) {
            hv--;
        }
    }
}

double complexity(const std::string& s) {
    size_t n = s.size();
    u64* r = new u64[n];
    u64* p = new u64[n];
    suffix_array(n, s, r, p);

    u64* h = new u64[n - 1];
    lcp(n, s, r, p, h);

    double k = 0.0;
    for (int i = 0; i < n - 1; i++) {
        if (h[i] > 0) {
            k += 1.0 / (double)h[i];
        }
    }

    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; r[i] + j < n; j++) {
            std::cout << s[r[i] + j];
        }
        std::cout << std::endl;
        if (i < n - 1) {
            std::cout << h[i] << std::endl;
        }
    }
    */

    delete r;
    delete p;
    delete h;
    return k;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: complexity <file>" << std::endl;
        exit(1);
    }
    srandom(time(NULL));
    std::string s = file_contents(argv[1]);
    std::cout << complexity(s) << std::endl;
    return 0;
}

