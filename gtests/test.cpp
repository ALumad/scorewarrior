#include "../src/models/actions/builders/ActionFactory.h"
#include "../src/models/Map.h"
#include "../src/models/Tick.h"
#include <gtest/gtest.h>

TEST(ActionFactory, CREATE_MAP)
{

    auto action = ActionsFactory::ActionFromLine("CREATE_MAP 31 32");
    action->Do();
    auto map_size = Singleton<Map>::instance().GetSize();
    ASSERT_TRUE(map_size.first == 31);
    ASSERT_TRUE(map_size.second == 32);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}