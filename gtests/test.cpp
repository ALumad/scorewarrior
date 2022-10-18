#include "models/actions/builders/ActionFactory.h"
#include "models/Map.h"
#include "models/Tick.h"
#include <gtest/gtest.h>
#include "utils/Point.h"
TEST(ActionFactory, CREATE_MAP)
{
    auto action = ActionsFactory::ActionFromLine("CREATE_MAP 31 32");
    action->Do();
    auto map_size = Singleton<Map>::instance().GetSize();
    ASSERT_TRUE(map_size.first == 31 && map_size.second == 32);
}

TEST(ActionFactory, SPAWN)
{
    std::size_t id = Singleton<Map>::instance()[{10,20}];
    ASSERT_TRUE(id == 0);
    auto action = ActionsFactory::ActionFromLine("SPAWN 1 10 20 50");
    action->Do();
    id = Singleton<Map>::instance()[{10,20}];
    ASSERT_TRUE(id == 1);
}

TEST(ActionFactory, MARCH)
{
    auto action = ActionsFactory::ActionFromLine("MARCH 1 11 21");
    action->Do();
    ASSERT_TRUE(action->Do() == IAction::STATUS::INPROGRESS);
}


TEST(ActionFactory, WAIT)
{
    ASSERT_TRUE(Singleton<Tick>::instance().GetTicks() == 0);
    auto action = ActionsFactory::ActionFromLine("WAIT 3");
    action->Do();
    ASSERT_TRUE(Singleton<Tick>::instance().GetTicks() == 3);
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}