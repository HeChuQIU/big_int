#include "gtest/gtest.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include "big_int.h"

TEST(BIG_INT, COMPARE_TO) {
    boost::mt19937 mt(time(0));
    for (int i = 0; i < (1 << 10); ++i) {
//        boost::multiprecision::cpp_int a0 = mt();
//        boost::multiprecision::cpp_int b0 = mt();
//        for (int j = 0; j < (1 << 3); ++j) {
//            a0 *= a0;
//            b0 *= b0;
//        }
//        a0 = mt() % 2 == 0 ? a0 : -a0;
//        b0 = mt() % 2 == 0 ? b0 : -b0;
        auto a0 = boost::multiprecision::cpp_int("2909976390831423376000000000");
        auto b0 = boost::multiprecision::cpp_int("7098838590000000000000000000");
        int c0;
        if (a0 > b0)
            c0 = 1;
        else if (a0 < b0)
            c0 = -1;
        else
            c0 = 0;

        big_int a1(to_string(a0));
        big_int b1(to_string(b0));
        int c1 = a1.compare_to(b1);

//        std::cout << a0 << std::endl << b0 << " " << c0 << std::endl
//                  << "===========================================" << std::endl
//                  << a1 << std::endl << b1 << " " << c1 << std::endl
//                  << std::endl;

        EXPECT_EQ(c0, c1) << a0 << std::endl << b0 << " " << c0 << std::endl
                          << "===========================================" << std::endl
                          << a1 << std::endl << b1 << " " << c1 << std::endl
                          << std::endl;
    }
}


TEST(BIG_INT, GET_NUMBER_LENGTH) {
    boost::mt19937 mt(time(0));
    for (int i = 0; i < (1 << 10); ++i) {
        boost::multiprecision::cpp_int a0 = mt();;
        for (int j = 0; j < (1 << 3); ++j) {
            a0 *= a0;
        }
        a0 = mt() % 2 == 0 ? a0 : -a0;
        a0 = a0 < 0 ? -a0 : a0;

        auto c0 = a0.str().size();

        big_int a1(to_string(a0));
        auto c1 = a1.get_number_length();

        EXPECT_EQ(c0, c1) << a0 << std::endl << c0 << std::endl
                          << "===========================================" << std::endl
                          << a1 << std::endl << c1 << std::endl;
    }
}

TEST(BIG_INT, ADD) {
    boost::mt19937 mt(time(0));
    for (int i = 0; i < (1 << 10); ++i) {
        boost::multiprecision::cpp_int a0 = mt();
        boost::multiprecision::cpp_int b0 = mt();
        for (int j = 0; j < (1 << 3); ++j) {
            a0 *= a0;
            b0 *= b0;
        }
        a0 = mt() % 2 == 0 ? a0 : -a0;
        b0 = mt() % 2 == 0 ? b0 : -b0;
        boost::multiprecision::cpp_int c0 = a0 + b0;

        big_int a1(to_string(a0));
        big_int b1(to_string(b0));
        big_int c1 = a1 + b1;

        EXPECT_EQ(to_string(c0), to_string(c1)) << a0 << std::endl << b0 << std::endl << c0 << std::endl
                                                << "===========================================" << std::endl
                                                << a1 << std::endl << b1 << std::endl << c1 << std::endl
                                                << std::endl;
    }
}


TEST(BIG_INT, SUBTRACT) {
    boost::mt19937 mt(time(0));
    for (int i = 0; i < (1 << 10); ++i) {
        boost::multiprecision::cpp_int a0 = mt();
        boost::multiprecision::cpp_int b0 = mt();
        for (int j = 0; j < (1 << 3); ++j) {
            a0 *= a0;
            b0 *= b0;
        }
        a0 = mt() % 2 == 0 ? a0 : -a0;
        b0 = mt() % 2 == 0 ? b0 : -b0;
        boost::multiprecision::cpp_int c0 = a0 - b0;

        big_int a1(to_string(a0));
        big_int b1(to_string(b0));
        big_int c1 = a1 - b1;

        EXPECT_EQ(to_string(c0), to_string(c1)) << a0 << std::endl << b0 << std::endl << c0 << std::endl
                                                << "===========================================" << std::endl
                                                << a1 << std::endl << b1 << std::endl << c1 << std::endl
                                                << std::endl;
    }
}


TEST(BIG_INT, MULTIPLY) {
    boost::mt19937 mt(time(0));
    for (int i = 0; i < (1 << 10); ++i) {
        boost::multiprecision::cpp_int a0 = mt();
        boost::multiprecision::cpp_int b0 = mt();
        for (int j = 0; j < (1 << 1); ++j) {
            a0 *= a0;
            b0 *= b0;
        }
        a0 = mt() % 2 == 0 ? a0 : -a0;
        b0 = mt() % 2 == 0 ? b0 : -b0;
        boost::multiprecision::cpp_int c0 = a0 * b0;

        big_int a1(to_string(a0));
        big_int b1(to_string(b0));
        big_int c1 = a1 * b1;

        EXPECT_EQ(to_string(c0), to_string(c1)) << a0 << std::endl << b0 << std::endl << c0 << std::endl
                                                << "===========================================" << std::endl
                                                << a1 << std::endl << b1 << std::endl << c1 << std::endl
                                                << std::endl;
    }
}


TEST(BIG_INT, DIVIDE) {
    boost::mt19937 mt(time(0));
    for (int i = 0; i < (1 << 10); ++i) {
        boost::multiprecision::cpp_int a0 = mt();
        boost::multiprecision::cpp_int b0 = mt();
        for (int j = 0; j < (1 << 1); ++j) {
            a0 *= a0;
            b0 *= b0;
        }
//        auto a0 = boost::multiprecision::cpp_int("-10008814980831423376");
//        auto b0 = boost::multiprecision::cpp_int("-709883859");
        a0 = mt() % 2 == 0 ? a0 : -a0;
        b0 = mt() % 2 == 0 ? b0 : -b0;
        boost::multiprecision::cpp_int c0 = a0 / b0;

        big_int a1(to_string(a0));
        big_int b1(to_string(b0));
        big_int c1 = a1 / b1;

        EXPECT_EQ(to_string(c0), to_string(c1)) << a0 << std::endl << b0 << std::endl << c0 << std::endl
                                                << "===========================================" << std::endl
                                                << a1 << std::endl << b1 << std::endl << c1 << std::endl
                                                << std::endl;
    }
}
