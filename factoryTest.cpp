// FactoryMethodTest.cpp
#include <gtest/gtest.h>
#include "factory.cpp"

TEST(FactoryMethodTest, WindowsDialogTest) {
    Application app;
    app.initialize("Windows");

    testing::internal::CaptureStdout();
    app.main();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Rendering Windows-style button."), std::string::npos);
    EXPECT_NE(output.find("Binding Windows OS click event."), std::string::npos);
    EXPECT_NE(output.find("Dialog closed."), std::string::npos);
}

TEST(FactoryMethodTest, WebDialogTest) {
    Application app;
    app.initialize("Web");

    testing::internal::CaptureStdout();
    app.main();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Rendering HTML button."), std::string::npos);
    EXPECT_NE(output.find("Binding web click event."), std::string::npos);
    EXPECT_NE(output.find("Dialog closed."), std::string::npos);
}

TEST(FactoryMethodTest, InvalidOSTest) {
    Application app;
    EXPECT_THROW(app.initialize("Linux"), std::runtime_error);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
