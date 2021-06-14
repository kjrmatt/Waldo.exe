#pragma once
#include <thread>

struct SpriteLoader {
	sf::Texture texture;
	sf::Sprite sprite;
	virtual void SetSpriteScale() = 0;
	SpriteLoader(const std::string &path){
		EDassets::decryptFile(path);
		texture.loadFromFile(path + ".png");
		sprite.setTexture(texture);
		increaseBar(BARUI::barload);
		EDassets::encryptFile(path + ".png");
		increaseBar(BARUI::barload);
	}
};

struct ARROWCURSOR : public SpriteLoader {
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getScaleArrow(), scaleresol.getScaleArrow()));
	}
	ARROWCURSOR(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
			sprite.setOrigin(68, 23);
		}
};

struct HANDCURSOR : public SpriteLoader {
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getScaleArrow(), scaleresol.getScaleArrow()));
	}
	HANDCURSOR(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
			sprite.setOrigin(110, 30);
		}
};

struct CIRCLECURSOR : public SpriteLoader {
	StaticObjAnimation AnimationCircle;
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getScaleCircleCursor(), scaleresol.getScaleCircleCursor()));
	}
	CIRCLECURSOR(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
			sprite.setOrigin(187, 180);
			AnimationCircle = StaticObjAnimation(&texture, sf::Vector2u(9,1), 0.06f);
		}
};

struct EXITICON : public SpriteLoader {
	int clickableX[2], clickableY[2];
	float exitWidth, exitHeight;
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getScaleExitIcon(), scaleresol.getScaleExitIcon()));
	}
	EXITICON(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
			exitWidth = (sprite.getTexture()->getSize().x) * scaleresol.getScaleExitIcon();
			exitHeight = (sprite.getTexture()->getSize().y) * scaleresol.getScaleExitIcon();
			sprite.setOrigin(sprite.getTexture()->getSize().x, 0);
			clickableX[0] = (sf::VideoMode::getDesktopMode().width) - exitWidth;
			clickableX[1] = sf::VideoMode::getDesktopMode().width;
			clickableY[0] = 0;
			clickableY[1] = exitHeight;
			sprite.setPosition(sf::VideoMode::getDesktopMode().width, 0);
		}
};

struct PAUSESCREEN : public SpriteLoader {
	sf::Vector2i screenSize;
	int rRangeClickX[2], rRangeClickY[2];
	//615 -> 791         353 -> 403
	int qRangeClickX[2], qRangeClickY[2];
	//615 -> 791         460 -> 510
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getFullScreenSpriteScale(), scaleresol.getFullScreenSpriteScale()));
	}
	PAUSESCREEN(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
			screenSize.x = sf::VideoMode::getDesktopMode().width;
			screenSize.y = sf::VideoMode::getDesktopMode().height;

			// Range Resume
			rRangeClickX[0] = screenSize.x * 0.4502196193;
			rRangeClickX[1] = screenSize.x * 0.5790629575;
			rRangeClickY[0] = screenSize.y * 0.4596354167;
			rRangeClickY[1] = screenSize.y * 0.5247395833;

			//Range Quit
			qRangeClickX[0] = screenSize.x * 0.4502196193;
			qRangeClickX[1] = screenSize.x * 0.5790629575;
			qRangeClickY[0] = screenSize.y * 0.5989583333;
			qRangeClickY[1] = screenSize.y * 0.6640625;
		}
	bool resumeInRange(const sf::Vector2i &mousePos){
		return ((mousePos.x >= rRangeClickX[0] && mousePos.x <= rRangeClickX[1]) && 
			(mousePos.y >= rRangeClickY[0] && mousePos.y <= rRangeClickY[1]));
	}
	bool quitInRange(const sf::Vector2i &mousePos) {
		return ((mousePos.x >= qRangeClickX[0] && mousePos.x <= qRangeClickX[1]) &&
			(mousePos.y >= qRangeClickY[0] && mousePos.y <= qRangeClickY[1]));
	}
};

struct GAMEEND : public SpriteLoader {
	sf::Vector2i screenSize;
	int cRangeClickX[2], cRangeClickY[2];
	//606 -> 759         454 -> 495
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getFullScreenSpriteScale(), scaleresol.getFullScreenSpriteScale()));
	}
	GAMEEND(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
			screenSize.x = sf::VideoMode::getDesktopMode().width;
			screenSize.y = sf::VideoMode::getDesktopMode().height;

			// Range continue
			cRangeClickX[0] = screenSize.x * 0.4436310395;
			cRangeClickX[1] = screenSize.x * 0.555636896;
			cRangeClickY[0] = screenSize.y * 0.5911458333;
			cRangeClickY[1] = screenSize.y * 0.64453125;
		}
	bool continueInRange(const sf::Vector2i &mousePos){
		return ((mousePos.x >= cRangeClickX[0] && mousePos.x <= cRangeClickX[1]) &&
			(mousePos.y >= cRangeClickY[0] && mousePos.y <= cRangeClickY[1]));
	}
};

struct MENULOGO : public SpriteLoader {
	virtual void SetSpriteScale() override {
		sprite.setScale(sf::Vector2f(scaleresol.getFullScreenSpriteScale(), scaleresol.getFullScreenSpriteScale()));
	}
	MENULOGO(const std::string &pathA)
		:SpriteLoader(pathA){
			SetSpriteScale();
		}
};

struct SOUNDEFFECT {
	sf::SoundBuffer buffer;
	sf::Sound sound;
	SOUNDEFFECT(const std::string &path){
		buffer.loadFromFile(path);
		sound.setBuffer(buffer);
		increaseBar(BARUI::barload);
	}
};

struct GAMEMUSIC {
	sf::Music music;
	GAMEMUSIC(const std::string &path){
		music.openFromFile(path);
		increaseBar(BARUI::barload);
	}
};

ARROWCURSOR *ArrowCursorObj;
HANDCURSOR *HandCursorObj;
CIRCLECURSOR *CircleCursorObj;
EXITICON *ExitIconObj;
MENULOGO *MenuLogoObj;
PAUSESCREEN *PauseScreenObj;
GAMEEND *WaldoFoundObj;
GAMEEND *GameOverObj;

GAMEMUSIC *Intromusic;
SOUNDEFFECT *WrongClickEffect;
SOUNDEFFECT *WallyFoundEffect;

MapProperty *MAP1;
MapProperty *MAP2;
MapProperty *MAP3;
MapProperty *MAP4;
MapProperty *MAP5;
MapProperty *MAP6;

static bool done = false;

void loadAssets(){
	ArrowCursorObj = new ARROWCURSOR("Assets/Cursors/ArrowCursor");
	HandCursorObj = new HANDCURSOR("Assets/Cursors/HandCursor");
	CircleCursorObj = new CIRCLECURSOR("Assets/Cursors/redcirclesprite");
	ExitIconObj = new EXITICON("Assets/Icon/InIcons/exit");
	MenuLogoObj = new MENULOGO("Assets/fsSprites/States/MenuUI");
	PauseScreenObj = new PAUSESCREEN("Assets/fsSprites/States/Pause");
	WaldoFoundObj = new GAMEEND("Assets/fsSprites/States/Found");
	GameOverObj = new GAMEEND("Assets/fsSprites/States/Gameover");

	Intromusic = new GAMEMUSIC("Assets/Audio/music/MenuMusic.wav");
	WrongClickEffect = new SOUNDEFFECT("Assets/Audio/SoundEffects/WrongClick.wav");
	WallyFoundEffect = new SOUNDEFFECT("Assets/Audio/SoundEffects/WallyFound.wav");

	MAP1 = new MapProperty("Assets/fsSprites/Maps/Map1", "Map1", GameTimer::m1TimeCounts);
	MAP2 = new MapProperty("Assets/fsSprites/Maps/Map2", "Map2", GameTimer::m2TimeCounts);
	MAP3 = new MapProperty("Assets/fsSprites/Maps/Map3", "Map3", GameTimer::m3TimeCounts);
	MAP4 = new MapProperty("Assets/fsSprites/Maps/Map4", "Map4", GameTimer::m4TimeCounts);
	MAP5 = new MapProperty("Assets/fsSprites/Maps/Map5", "Map5", GameTimer::m5TimeCounts);
	MAP6 = new MapProperty("Assets/fsSprites/Maps/Map6", "Map6", GameTimer::m6TimeCounts);

	done = true;
}

void windowLoad(){
	sf::RenderWindow loadWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width * 0.50, sf::VideoMode::getDesktopMode().height * 0.50), "Where's Wally?", sf::Style::None);
	std::unique_ptr<sf::Texture> textureLoading = std::make_unique<sf::Texture>();
	std::unique_ptr<sf::Sprite> spriteLoading = std::make_unique<sf::Sprite>();
	float spriteScale = (sf::VideoMode::getDesktopMode().height * 0.50) / 1080.0f;
	textureLoading->loadFromFile("Assets/fsSprites/States/Loading.png");
	spriteLoading->setTexture(*textureLoading);
	spriteLoading->setScale(spriteScale, spriteScale);
	BARUI::SETPOSITION(loadWindow);
	std::thread threadLoadAssets(loadAssets);
	while (loadWindow.isOpen()){
		sf::Event evnt;
		while (loadWindow.pollEvent(evnt)){
		if (evnt.type == sf::Event::Closed)
			loadWindow.close();
		}
		loadWindow.clear();
		loadWindow.draw(*spriteLoading);
		loadWindow.draw(BARUI::barlimit);
		loadWindow.draw(BARUI::barload);
		loadWindow.display();

		if (done)
			loadWindow.close();
	}
	threadLoadAssets.join();

}