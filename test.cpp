#include "pch.h"
#include "../GameViewer/Game.cpp"
#include "../GameViewer/GameModel.cpp"
#include "../GameViewer/WebDataReader.cpp"

namespace {


	class WebDateReaderTest : public ::testing::Test {
	protected:

		WebDateReaderTest() {
		}

		~WebDateReaderTest() override {

		}

		void SetUp() override {

		}

		void TearDown() override {

		}
	};

	// Test Web Image Reader
	TEST(WebDateReaderTest, ImageReaderTest) {
		WebDataReader* reader = new WebDataReader();
		std::string imageUrl = "https://securea.mlb.com/assets/images/7/9/6/280664796/cuts/320x180/cut.jpg";
		QImage* image = new QImage();
		CURLcode res;
		res = (CURLcode)reader->ReadImageFromURL(imageUrl, image);
		
		QImage* testImage = new QImage("TestImage.jpg");
		EXPECT_TRUE(*testImage == *image);

		delete reader;
		delete testImage;
		delete image;

	}

	// Test Web Json Reader
	TEST(WebDateReaderTest, JsonReaderTest) {
		Json::Value root;
		WebDataReader* reader = new WebDataReader();
		std::string url = "http://statsapi.mlb.com/api/v1/schedule?hydrate=game(content(editorial(recap))),decisions&date=2018-06-10&sportId=1";
		reader->ReadJSONFromURL(url, &root);
		
		EXPECT_EQ(15, root["totalGames"].asInt());
		delete reader;
	}

	// Test Web Json Reader
	TEST(WebDateReaderTest, JsonReaderGameTest) {
		Json::Value root;
		CURLcode res;
		WebDataReader* reader = new WebDataReader();
		GameModel* gameModel = new GameModel();
		std::string url = "http://statsapi.mlb.com/api/v1/schedule?hydrate=game(content(editorial(recap))),decisions&date=2018-06-10&sportId=1";

		reader->ReadJSONFromURL(url, &root);
	

		Json::Value games = root["dates"][0]["games"];

		Json::Value::iterator it;
		for (it = games.begin(); it != games.end(); ++it)
		{
			// Create Game
			Game* game = new Game(*it);


			gameModel->getList()->push_back(game);
		}
		EXPECT_EQ(gameModel->getList()->at(0)->getCalendarEventID(), "14-530376-2018-06-10");

		delete reader;
	}
}



int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	std::cout << "Tests Running: " << std::endl;
	return RUN_ALL_TESTS();

}