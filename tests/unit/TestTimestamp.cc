#include "kafka/Timestamp.h"

#include "librdkafka/rdkafka.h"

#include "gtest/gtest.h"

#include <regex>

namespace Kafka = KAFKA_API;

TEST(Timestamp, Basic)
{
    std::int64_t msSinceEpoch = 1577966461123;

    Kafka::Timestamp naTypeTime(msSinceEpoch);
    EXPECT_EQ(Kafka::Timestamp::Type::NotAvailable, naTypeTime.type);
    EXPECT_EQ(msSinceEpoch, naTypeTime.msSinceEpoch);
    // E.g, "2020-01-02 12:01:01.123"
    std::regex reMatch(R"(2020-01-.. ..:01:01\.123)");
    EXPECT_TRUE(std::regex_match(naTypeTime.toString(), reMatch));

    Kafka::Timestamp createTime(msSinceEpoch, Kafka::Timestamp::Type::CreateTime);
    // E.g, "CreateTime[2020-01-02 12:01:01.123]"
    std::regex reMatchCreateTime(R"(CreateTime\[2020-01-.. ..:01:01\.123\])");
    EXPECT_TRUE(std::regex_match(createTime.toString(), reMatchCreateTime));

    Kafka::Timestamp logAppendTime(msSinceEpoch, Kafka::Timestamp::Type::LogAppendTime);
    // E.g, "LogAppendTime[2020-01-02 12:01:01.123]"
    std::regex reMatchLogAppendTime(R"(LogAppendTime\[2020-01-.. ..:01:01\.123\])");
    EXPECT_TRUE(std::regex_match(logAppendTime.toString(), reMatchLogAppendTime));
}

TEST(Timestamp, FromLibRdkafka)
{
    std::int64_t msSinceEpoch = 1577966461123;

    Kafka::Timestamp naTypeTime(msSinceEpoch, RD_KAFKA_TIMESTAMP_NOT_AVAILABLE);
    EXPECT_EQ(Kafka::Timestamp::Type::NotAvailable, naTypeTime.type);
    // E.g, "2020-01-02 12:01:01.123"
    std::regex reMatch(R"(2020-01-.. ..:01:01\.123)");
    EXPECT_TRUE(std::regex_match(naTypeTime.toString(), reMatch));

    Kafka::Timestamp createTime(msSinceEpoch, RD_KAFKA_TIMESTAMP_CREATE_TIME);
    EXPECT_EQ(Kafka::Timestamp::Type::CreateTime, createTime.type);
    // E.g, "CreateTime[2020-01-02 12:01:01.123]"
    std::regex reMatchCreateTime(R"(CreateTime\[2020-01-.. ..:01:01\.123\])");
    EXPECT_TRUE(std::regex_match(createTime.toString(), reMatchCreateTime));

    Kafka::Timestamp logAppendTime(msSinceEpoch, RD_KAFKA_TIMESTAMP_LOG_APPEND_TIME);
    EXPECT_EQ(Kafka::Timestamp::Type::LogAppendTime, logAppendTime.type);
    // E.g, "LogAppendTime[2020-01-02 12:01:01.123]"
    std::regex reMatchLogAppendTime(R"(LogAppendTime\[2020-01-.. ..:01:01\.123\])");
    EXPECT_TRUE(std::regex_match(logAppendTime.toString(), reMatchLogAppendTime));
}

