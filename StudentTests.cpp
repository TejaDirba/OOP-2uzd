#include <gtest/gtest.h>
#include "Student.h"

TEST(StudentRuleOfFive, CopyMove) {
    Student a("Jonas","Jonaitis");
    a.setNd({9,8,7});
    a.setEgzaminas(10);
    a.calculateFinalGrades();
    Student b(a);
    EXPECT_EQ(b.getVardas(),"Jonas");
    Student c(std::move(b));
    EXPECT_EQ(c.getPavarde(),"Jonaitis");
    Student d;
    d = a;
    EXPECT_EQ(d.getEgzaminas(),10);
    Student e;
    e = std::move(d);
    EXPECT_GT(e.getGalutinisVid(),0);
}

TEST(StudentIO, Stream) {
    Student a("A","B");
    a.setNd({5,5,5});
    a.setEgzaminas(5);
    a.calculateFinalGrades();
    std::stringstream ss;
    ss << a;
    Student x;
    ss >> x;
    EXPECT_EQ(x.getVardas(),"A");
}

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
