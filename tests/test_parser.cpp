#include "Msg.hpp"
#include "parser.hpp"
#include "gtest/gtest.h"

TEST(ParserTest, ParsesBasicMessage)
{
  std::string raw = "CMD param1 param2";
  Msg msg = parse(raw);
  EXPECT_EQ(msg.command, "CMD");
  EXPECT_EQ(msg.params.size(), 2);
  EXPECT_EQ(msg.params[0], "param1");
  EXPECT_EQ(msg.params[1], "param2");
}

TEST(ParserTest, ParsesMessageWithPrefix)
{
  std::string raw = ":nick!username@host CMD param1 param2";
  Msg msg = parse(raw);
  EXPECT_EQ(msg.prefix, ":nick!username@host");
  EXPECT_EQ(msg.command, "CMD");
  EXPECT_EQ(msg.params.size(), 2);
  EXPECT_EQ(msg.params[0], "param1");
  EXPECT_EQ(msg.params[1], "param2");
}

TEST(ParserTest, ParsesNick)
{
  std::string raw = "NICK John";
  Msg msg = parse(raw);
  EXPECT_EQ(msg.prefix, "");
  EXPECT_EQ(msg.command, "NICK");
  EXPECT_EQ(msg.params.size(), 1);
  EXPECT_EQ(msg.params[0], "John");
}

TEST(ParserTest, ParsesPrivmsgHi)
{
  std::string raw = ":test!~test@test.com PRIVMSG #channel :Hi!";
  Msg msg = parse(raw);
}

TEST(ParserTest, ParsesPrivmsgHello)
{
  std::string raw = ":Scionwest!Scionwest@555.55.55.555 PRIVMSG #mychannel :Hello everyone!";
  Msg msg = parse(raw);
  EXPECT_EQ(msg.prefix, ":Scionwest!Scionwest@555.55.55.555");
}
