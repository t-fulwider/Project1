/*#include <catch2/catch_test_macros.hpp>
#include <random>

#include "AVL.h"

using namespace std;

//===== Invalid Commands =====//

TEST_CASE("Insert() with invalid name", "[flag]"){

	AVL tree;
	bool result = tree.Insert("Tanner/Ful", "12345678");
	REQUIRE(!result);
}
TEST_CASE("Insert() with invalid UFID", "[flag]"){
	
	AVL tree;
	bool result = tree.Insert("Tanner", "1");
	REQUIRE(!result);
}
TEST_CASE("Insert() with empty name", "[flag]"){

	AVL tree;
	bool result = tree.Insert("", "12345678");
	REQUIRE(!result);
}

TEST_CASE("Remove(ufid) with invalid UFID", "[flag]"){
	
	AVL tree;
	bool result = tree.RemoveID("1");
	REQUIRE(!result);
}
TEST_CASE("Search(ufid) with invalid UFID", "[flag]"){
	
	AVL tree;
	string result = tree.SearchID("abcdefgh");
	REQUIRE(result.empty());
}
TEST_CASE("Search(name) with invalid name", "[flag]"){
	
	AVL tree;
	vector<string> result = tree.SearchName("Tanner6");

	REQUIRE(result.empty());
}

//===== Rotation Cases =====//

TEST_CASE("Insert and Rotation Cases", "[flag]") {

	AVL tree;
	// Left Rotation (Right Right)
	tree.Insert("NodeOne", "12345677");
	tree.Insert("NodeTwo", "12345679");
	tree.Insert("NodeThree", "12345680");
	vector<string> actualOutput = tree.TraversePostorder("ufid");
	vector<string> expectedOutput = {"12345677", "12345680", "12345679"};
	REQUIRE(actualOutput == expectedOutput);

	// Right Rotation (Left Left)
	tree.Insert("NodeFour", "12345676");
	tree.Insert("NodeFive", "12345675");
	actualOutput = tree.TraversePostorder("ufid");
	expectedOutput = {"12345675", "12345677", "12345676", "12345680", "12345679"};
	REQUIRE(actualOutput == expectedOutput);

	// Left Right Rotation
	AVL tree2;
	tree2.Insert("NodeOne", "12345678");
	tree2.Insert("NodeTwo", "12345676");
	tree2.Insert("NodeThree", "12345677");
	actualOutput = tree2.TraversePostorder("ufid");
	expectedOutput = {"12345676", "12345678", "12345677"};
	REQUIRE(actualOutput == expectedOutput);

	// Right Left Rotation
	AVL tree3;
	tree3.Insert("NodeOne", "12345677");
	tree3.Insert("NodeTwo", "12345679");
	tree3.Insert("NodeThree", "12345678");
	actualOutput = tree3.TraversePostorder("ufid");
	expectedOutput = {"12345677", "12345679", "12345678"};
	REQUIRE(actualOutput == expectedOutput);
}

//===== Insert and Remove Nodes in Large Tree =====//

TEST_CASE("BST Insert Large", "[flag]"){

	random_device rd;
	mt19937 gen(rd()); // recieved from https://stackoverflow.com/questions/7560114/random-number-c-in-some-range

	AVL tree;
	vector<int> expectedOutput = {};
	vector<string> actualOutput = {};

	uniform_int_distribution<> distr(10000000, 99999999); // define the range
	while(expectedOutput.size() < 100)
	{
		int randomInput = distr(gen);
		if (count(expectedOutput.begin(), expectedOutput.end(), randomInput) == 0)
		{
			expectedOutput.push_back(randomInput);
			tree.Insert("Name", to_string(randomInput));
		}
	}

	actualOutput = tree.TraverseInorder("ufid");
	REQUIRE(expectedOutput.size() == actualOutput.size());
	//REQUIRE_FALSE(expectedOutput == actualOutput);    //This assertion can be wrong. Don't use
	sort(expectedOutput.begin(), expectedOutput.end());
	bool result = true;
	for (int i = 0; i < actualOutput.size(); i++)
	{
		if (stoi(actualOutput[i]) != expectedOutput[i])
		{
			result = false;
			break;
		}
	}
	REQUIRE(result);

	// DELETE //

	for(int i = 0; i < 10; i++)
	{
		uniform_int_distribution<> distr(0, expectedOutput.size() - 1); // define the range
		int randomInput = distr(gen);
		expectedOutput.erase(expectedOutput.begin() + randomInput);
		tree.RemoveInorder(randomInput);
	}

	actualOutput = tree.TraverseInorder("ufid");
	REQUIRE(expectedOutput.size() == actualOutput.size());
	//REQUIRE_FALSE(expectedOutput == actualOutput);    //This assertion can be wrong. Don't use
	sort(expectedOutput.begin(), expectedOutput.end());
	for (int i = 0; i < actualOutput.size(); i++)
	{
		if (stoi(actualOutput[i]) != expectedOutput[i])
		{
			result = false;
			break;
		}
	}
	REQUIRE(result);
}

//===== Insert updates height correctly =====//
TEST_CASE("Height", "[flag]"){

	AVL tree;
	tree.Insert("Tanner", "12345678");
	tree.Insert("Tanner", "12345675");
	tree.Insert("Tanner", "12345679");
	tree.Insert("Tanner", "12345677");

	REQUIRE(tree.PrintLevelCount() == 3);

	tree.Insert("Tanner", "12345676");
	REQUIRE(tree.PrintLevelCount() == 3);
	tree.RemoveID("12345679");
	REQUIRE(tree.PrintLevelCount() == 3);
}

//===== SearchID works =====//
TEST_CASE("SearchID", "[flag]"){

	AVL tree;
	tree.Insert("TannerOne", "12345678");
	tree.Insert("TannerTwo", "12345676");
	tree.Insert("TannerThree", "12345679");
	tree.Insert("TannerFour", "12345677");
	string result = "TannerThree";

	REQUIRE(!tree.SearchID("12345679").empty());
	REQUIRE(tree.SearchID("12345679") == result);
}

//===== Deletion Cases =====//
TEST_CASE("Deletion cases", "[flag]")
{
	AVL tree;
	tree.Insert("Brandon", "35679999");
	tree.Insert("Brandon", "45679999");
	tree.Insert("Brandon", "55679999");
	tree.RemoveID("35679999");

	vector<string> expectedOutput = {"45679999", "55679999"};
	REQUIRE(tree.PrintLevelCount() == 2);
	REQUIRE(tree.TraversePreorder("ufid") == expectedOutput);

	tree.Insert("Brandon", "35679999");
	tree.Insert("Brandon", "25679999");
	REQUIRE(tree.PrintLevelCount() == 3);
	tree.RemoveID("35679999");

	expectedOutput = {"45679999", "25679999", "55679999"};
	REQUIRE(tree.PrintLevelCount() == 2);
	REQUIRE(tree.TraversePreorder("ufid") == expectedOutput);

	tree.Insert("Brandon", "35679999");
	tree.Insert("Brandon", "15679999");
	REQUIRE(tree.PrintLevelCount() == 3);
	tree.RemoveID("25679999");

	expectedOutput = {"45679999", "35679999", "15679999", "55679999"};
	REQUIRE(tree.PrintLevelCount() == 3);
	REQUIRE(tree.TraversePreorder("ufid") == expectedOutput);
}

//===== Edge Cases =====//
TEST_CASE("Remove nonexistent UFID", "[flag]")
{
	AVL tree;
	tree.Insert("Tanner", "12345678");
	REQUIRE(!tree.RemoveID("12345679"));
}
TEST_CASE("Insert ID that already exists", "[flag]")
{
	AVL tree;
	tree.Insert("Tanner", "12345678");
	REQUIRE(!tree.Insert("John", "12345678"));
}
TEST_CASE("RemoveInorder with invalid index", "[flag]")
{
	AVL tree;
	tree.Insert("Tanner", "12345678");
	REQUIRE(!tree.RemoveInorder(2));
}
TEST_CASE("printLevelCount with empty tree", "[flag]")
{
	AVL tree;
	tree.Insert("Tanner", "12345678");
	REQUIRE(tree.PrintLevelCount() == 1);
	tree.RemoveInorder(0);
	REQUIRE(tree.PrintLevelCount() == 0);
}*/