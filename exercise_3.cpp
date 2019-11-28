#include <stdexcept>
#include <gtest/gtest.h>

class TMyException : public std::logic_error {
    std::string message;
public:
    explicit TMyException(const std::string& str = {})
        :std::logic_error(str), message(str) {}
    virtual TMyException& operator<<(const std::string& str)
    {
        message += str;
        return *this;
    }
    const char* what() const noexcept override
    {
        return message.c_str();
    }
    ~TMyException() override = default;
};

class TMyException1 : public TMyException {};
struct TMyException2 : TMyException {
    explicit TMyException2(const std::string& str) : TMyException(str) {}
};

TEST(TestExercise3, Exceptions) {
    TMyException1 exception1;
    exception1 << "exception1" << "!";
    EXPECT_STREQ(exception1.what(), "exception1!");

    EXPECT_THROW(throw TMyException1(), std::exception);
    EXPECT_THROW(throw TMyException1(), std::logic_error);
    EXPECT_THROW(throw TMyException1(), TMyException);

    EXPECT_THROW(throw TMyException2("except"), TMyException);
    EXPECT_STREQ(TMyException2("except").what(), "except");
    EXPECT_STREQ((TMyException2("except") << "!").what(), "except!");
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
