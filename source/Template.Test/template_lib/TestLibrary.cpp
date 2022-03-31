#include <gtest/gtest.h>
#include <template_lib/Types.h>
#include <template_lib/Library.h>

namespace ddahlkvist
{

	class LibraryFixture : public testing::Test 
	{
	public:
		LibraryFixture()
		{}

	protected:
		void SetUp() override
		{
		}

		void TearDown() override
		{
		}
	};

	TEST_F(LibraryFixture, instance_returnsNullByDefault)
	{
		EXPECT_EQ(Library::instance(), nullptr);
	}

	TEST_F(LibraryFixture, instance_canCreateAndDestroy)
	{
		Library::createLibrary();
		EXPECT_NE(Library::instance(), nullptr);
		Library::destroyLibrary();
		EXPECT_EQ(Library::instance(), nullptr);
	}

}

