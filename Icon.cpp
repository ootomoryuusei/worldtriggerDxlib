#include "Icon.h"
#include"Tile.h"
#include"Player1.h"
#include"Engine/CsvReader.h"
#include"PlayScene.h"
#include "ImGui/imgui.h"


Icon::Icon(GameObject* parent) : Object3D(parent)
{
	/*std::string DLC = "Assets//Image//CharacterIcon//";
	csv_ = new CsvReader();
	csv_->Load("Assets//Character//CharacterStatus.csv");
	int FN2DLine;
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "FileName2D") {
			FN2DLine = x;
		}
	}
	for (int y = 1; y < csv_->GetHeight() ; y++) {
		std::string graphName;
		graphName = csv_->GetString(FN2DLine, y);
		std::string flPath;
		flPath = DLC + graphName;
		hChSlIcon_.push_back(LoadGraph(flPath.c_str()));
	}
	static int i = 0;
	for (auto itr : hChSlIcon_) {
		assert(itr >= 0);
		SIZE_2D graphsize;
		GetGraphSize(itr, &graphsize.x, &graphsize.y);
		graphsize.halfX = graphsize.x / 2.0f;
		graphsize.halfY = graphsize.y / 2.0f;
		hChSlGraphSize_.push_back({ graphsize.x,graphsize.y,graphsize.halfX,graphsize.halfY});
		hChSlPos_.push_back({ 0 + (float)graphsize.x * i,0 });
		i++;
	}
	i = 0;

	csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv");
	FN2DLine = 0;
	DLC = "Assets//Image//TriggerIcon//";
	for (int x = 0; x < csv_->GetWidth(0); x++) {
		if (csv_->GetString(x, 0) == "FileName2D") {
			FN2DLine = x;
		}
	}
	for (int y = 1; y < csv_->GetHeight(); y++) {
		std::string graphName;
		graphName = csv_->GetString(FN2DLine, y);
		std::string flPath;
		flPath = DLC + graphName;
		hWpSlIcon_.push_back(LoadGraph(flPath.c_str()));
	}
	for (auto itr : hWpSlIcon_) {
		assert(itr >= 0);
		SIZE_2D graphsize;
		GetGraphSize(itr, &graphsize.x, &graphsize.y);
		graphsize.halfX = graphsize.x / 2.0f;
		graphsize.halfY = graphsize.y / 2.0f;
		hWpSlGraphSize_.push_back({ graphsize.x,graphsize.y,graphsize.halfX,graphsize.halfY });
		hWpSlPos_.push_back({ 0 + (float)graphsize.x * i,200 });
		i++;
	}
	i = 0;

	for (auto itr : hChSlPos_) {
		CSPosition_.push_back(itr);
	}

	for (auto itr : hWpSlPos_) {
		WSPosition_.push_back(itr);
	}*/

	
	
	hTile = LoadGraph("Assets//Image//Tile.png");
	assert(hTile >= 0);
	hOnTile = LoadGraph("Assets//Image//OnTile.png");
	assert(hOnTile >= 0);
	hTileFrame = LoadGraph("Assets//Image//TileSelectFrame.png");
	assert(hTileFrame >= 0);
	hPIcon = LoadGraph("Assets//Image//pIcon.png");
	assert(hPIcon >= 0);
	hMainCircle = LoadGraph("Assets//Image//MainTriggerCircle.png");
	assert(hMainCircle >= 0);
	hSubCircle = LoadGraph("Assets//Image//SubTriggerCircle.png");
	assert(hSubCircle >= 0);
	hChSlUI_ = LoadGraph("Assets//Image//CharacterSelectUI.png");
	assert(hChSlUI_ >= 0);

	int count = 0;
	float xpos = 1100;
	float ypos = 600;
	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			if (j % 2 == 1) {
				pTile[i][j].position = { xpos - j * 26, ypos - 28 / 2 - i * 28 };
			}
			else {
				pTile[i][j].position = { xpos - j * 26, ypos - i * 28 };
			}
			pTile[i][j].num = count;
			count++;
		}
	}
	prevKey = false;
	prevX = 0;
	prevY = 0;
	cX = 0;
	cY = 0;
	compWay = false;

	//アイコンの画像サイズの取得とセット
	GetGraphSize(hPIcon, &PgraphSize.x, &PgraphSize.y);
	PgraphSize.halfX = PgraphSize.x / 2.0f;
	PgraphSize.halfY = PgraphSize.y / 2.0f;
	GetGraphSize(hMainCircle, &MCgraphSize.x, &MCgraphSize.y);
	MCgraphSize.halfX = MCgraphSize.x / 2.0f;
	MCgraphSize.halfY = MCgraphSize.y / 2.0f;
	GetGraphSize(hSubCircle, &SCgraphSize.x, &SCgraphSize.y);
	SCgraphSize.halfX = SCgraphSize.x / 2.0f;
	SCgraphSize.halfY = SCgraphSize.y / 2.0f;
	GetGraphSize(hTile, &TgraphSize.x, &TgraphSize.y);
	TgraphSize.halfX = TgraphSize.x / 2.0f;
	TgraphSize.halfY = TgraphSize.y / 2.0f;
	GetGraphSize(hChSlUI_, &CSgraphSize.x, &CSgraphSize.y);
	CSgraphSize.halfX = CSgraphSize.x / 2.0f;
	CSgraphSize.halfY = CSgraphSize.y / 2.0f;
	

	

	SetTrigger = { { {"ASTEROID",true},{"MOONBLADE",false},{"FREE",false},{"SHIELD",false}}, //Mainの初期化,
		{ {"MOONBLADE",false},{"FREE",false},{"SHIELD",false},{"ASTEROID",true}}}; //Subの初期化

	

	SetTriggerParam(SetTrigger);

	PIpos = { 500, 500 };

	state_ = SELECT;
}

Icon::~Icon()
{
	if (hTile > 0) {
		DeleteGraph(hTile);
		hTile = -1;
	}
	if (hTileFrame > 0) {
		DeleteGraph(hTileFrame);
		hTileFrame = -1;
	}
	if (hPIcon > 0) {
		DeleteGraph(hPIcon);
		hPIcon = -1;
	}
	DEL(hSubCircle, 0);
}

void Icon::Update()
{
	

	Player1* pl1 = GetParent()->FindGameObject<Player1>();
	Tile* tile = GetParent()->FindGameObject<Tile>();
	VECTOR Tposition;
	VECTOR Pposition = pl1->GetPosition();
	switch (state_) {
	case SELECT:
	{
		/*size_t index = 0;
		for (auto itr : hChSlIcon_) {
			if (PointInBox(mousePos, CSPosition_[index], {(float)hChSlGraphSize_[index].x,(float)hChSlGraphSize_[index].y})) {
				if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
					CSPosition_[index] = { mousePos.x - hChSlGraphSize_[index].halfX,mousePos.y - hChSlGraphSize_[index].halfY };
				}
			}

			if (PointInBox(CSPosition_[index], { 750, 350, }, { (float)CSgraphSize.x, (float)CSgraphSize.y })) {
				CSPosition_[index] = { 750,350 };
			}
			index++;
		}
		index = 0;
		for (auto itr : hWpSlIcon_) {
			if (PointInBox(mousePos, WSPosition_[index], { (float)hWpSlGraphSize_[index].x,(float)hWpSlGraphSize_[index].y })) {
				if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
					WSPosition_[index] = { mousePos.x - hWpSlGraphSize_[index].halfX,mousePos.y - hWpSlGraphSize_[index].halfY };
				}
				else {
					for (auto itr : SIUFPosition_) {
						int i = 0;
						if (PointInBox(WSPosition_[index], itr, { (float)SIFgraphSize.x,(float)SIFgraphSize.y })) {
							WSPosition_[index] = itr;
						}
						i++;
					}
				}
			}
			
			
			index++;
		}
		index = 0;*/

		if (CheckHitKey(KEY_INPUT_RETURN)) {
			pl1 = GetParent()->FindGameObject<Player1>();
			/*icon = GetParent()->FindGameObject<Icon>();*/
			pl1->SetMyTrigger(SetTrigger);
			pl1->SetState_(STEP1);
			tile->SetState_(STEP1);
			this->SetState_(STEP1);
		}
		break;
	}
	case STEP1:
	{
		break;
	}
	default:
		break;
	}
	/*OtNum = { GetPlayerOnTileNum() };
	TCenter = { pTile[OtNum.x][OtNum.y].position.x + TgraphSize.halfX, pTile[OtNum.x][OtNum.y].position.y + TgraphSize.halfY };*/
	/*if (PointInBox(mousePos, PIpos, { (float)MCgraphSize.x, (float)MCgraphSize.y })) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			StartAngle -= 0.1f;
			Angle -= 0.1f;
		}
		if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
			StartAngle += 0.1f;
			Angle += 0.1f;
		}
	}*/

	if (PointInBox(mousePos, PIpos, { (float)PgraphSize.x, (float)PgraphSize.y })){
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			PIpos = { mousePos.x - PgraphSize.halfX,mousePos.y - PgraphSize.halfY};
			//pl1->SetPosition(mousePos.x,0.0,mousePos.y);
		}
		else {
			for (int i = 0; i < z; i++) {
				for (int j = 0; j < x; j++) {
					if (z - i <= 2 || z - i >= 10) {
						if (PointInBox(mousePos, { pTile[i][j].position.x,pTile[i][j].position.y }
							, { (float)TgraphSize.x,(float)TgraphSize.y })) {
							PIpos = { pTile[i][j].position.x ,pTile[i][j].position.y  };
						}
					}
				}
			}
		}
	}

	
	
	KeyInput();

	

	/*ImGui::Begin("position");
	ImGui::InputFloat("X", &PIpos.x);
	ImGui::InputFloat("Y", &PIpos.y);
	ImGui::End();*/
}

void Icon::Draw()
{
	Player1* pl1 = GetParent()->FindGameObject<Player1>();
	Tile* tile = GetParent()->FindGameObject<Tile>();
	VECTOR Tposition;
	VECTOR Pposition = pl1->GetPosition();
	switch (state_)
	{
	case SELECT:
	{
		DrawGraph(750, 0, hSlIcUI_, TRUE);
		DrawGraph(750, 350, hChSlUI_, TRUE);

		/*size_t index = 0;
		for (auto itr : hChSlIcon_) {
			DrawGraph(CSPosition_[index].x, CSPosition_[index].y, itr, TRUE);
#if 0
			DrawBoxAA(CSPosition_[index].x, CSPosition_[index].y, CSPosition_[index].x
				+ hChSlGraphSize_[index].x, CSPosition_[index].y + hChSlGraphSize_[index].y, GetColor(255, 0, 0), FALSE);
#endif
			index++;
		}
		index = 0;
		for (auto itr : hWpSlIcon_) {
			DrawGraph(WSPosition_[index].x, WSPosition_[index].y, itr, TRUE);
#if 0
			DrawBoxAA(WSPosition_[index].x, WSPosition_[index].y, WSPosition_[index].x
				+ hWpSlGraphSize_[index].x, WSPosition_[index].y + hWpSlGraphSize_[index].y, GetColor(255, 0, 0), FALSE);
#endif
			index++;
		}
		index = 0;
		
		for (auto itr : SIUFPosition_) {
			DrawGraph(itr.x, itr.y, hSlIcUIFrame_, TRUE);
		}*/
		break;
	}
	case STEP1:
	{
		int main, sub;
		main = GetSelectedTrigger(SetTrigger).x;
		sub = GetSelectedTrigger(SetTrigger).y;


		for (int i = 0; i < z; i++) {
			for (int j = 0; j < x; j++) {
				DrawGraph(pTile[i][j].position.x, pTile[i][j].position.y, hTile, TRUE);
				if (z - i <= 2 || z - i >= 10) {
					DrawGraph(pTile[i][j].position.x, pTile[i][j].position.y, hOnTile, TRUE);
#if 0 
					DrawBoxAA(pTile[i][j].position.x, pTile[i][j].position.y, pTile[i][j].position.x + TgraphSize.x, pTile[i][j].position.y + TgraphSize.y
						, GetColor(0, 0, 255), FALSE); //tileのボックス
#endif
				}
			}
		}
		XMFLOAT2 PICenter = { PIpos.x + PgraphSize.halfX, PIpos.y + PgraphSize.halfY };

		DrawCircleGauge(PICenter.x + PgraphSize.halfX, PICenter.y + PgraphSize.halfY, SetTrigger.Main[main].angle, hMainCircle, SetTrigger.Main[main].startAngle, SetTrigger.Main[main].rangeSize);
		DrawCircleGauge(PICenter.x + PgraphSize.halfX, PICenter.y + PgraphSize.halfY, SetTrigger.Sub[sub].angle, hSubCircle, SetTrigger.Sub[sub].startAngle, SetTrigger.Sub[sub].rangeSize);
		/*DrawGraph(pTile[cY][cX].position.x, pTile[cY][cX].position.y, hTileFrame, TRUE);*/
		/*DrawGraph(0, 0, hSelectIcon, TRUE);
		DrawGraph(0, 0, hATIcon, TRUE);*/
		DrawGraph(PICenter.x, PICenter.y, hPIcon, TRUE);
#if 0 //ボックス
		DrawBoxAA(PIpos.x, PIpos.y,
			PIpos.x + PgraphSize.x, PIpos.y + PgraphSize.y, GetColor(0, 0, 255), FALSE); //playerIconのボックス
		DrawBoxAA(TCenter.x - MCgraphSize.halfX * SetTrigger.Main[main].rangeSize, TCenter.y - MCgraphSize.halfY * SetTrigger.Main[main].rangeSize,
			TCenter.x + MCgraphSize.halfX * SetTrigger.Main[main].rangeSize, TCenter.y + MCgraphSize.halfY * SetTrigger.Main[main].rangeSize, GetColor(255, 0, 0), FALSE); //メインサークルのボックス
		DrawBoxAA(TCenter.x - SCgraphSize.halfX * SetTrigger.Sub[sub].rangeSize, TCenter.y - SCgraphSize.halfY * SetTrigger.Sub[sub].rangeSize,
			TCenter.x + SCgraphSize.halfX * SetTrigger.Sub[sub].rangeSize, TCenter.y + SCgraphSize.halfY * SetTrigger.Sub[sub].rangeSize, GetColor(0, 0, 255), FALSE); //サブサークルのボックス

#endif
		break;
	}
	default:
		break;
	}
	
}

XMFLOAT2 Icon::GetPIconPos()
{
	XMFLOAT2 tile3DPosition;
	Tile* tile = GetParent()->FindGameObject<Tile>();
	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			if (pTile[i][j].position.x == PIpos.x && pTile[i][j].position.y == PIpos.y) {
				tile3DPosition = { tile->GetTilesData(i, j).position.x,tile->GetTilesData(i, j).position.z};
				return tile3DPosition;
			}
		}
	}
	return XMFLOAT2(0,0);
}

void Icon::KeyInput()
{
	Player1* pl1 = GetParent()->FindGameObject<Player1>();
	getStatus = pl1->GetCStatus();
	int size = way.size();

	if (CheckHitKey(KEY_INPUT_UP)) {
		if (prevKey == false) {
			prevY = cY;
			cY += 1;
			if (cY > z - 1) {
				cY = prevY;
			}
		}
		prevKey = true;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN)) {
		if (prevKey == false) {
			prevY = cY;
			cY -= 1;
			if (cY < 0) {
				cY = prevY;
			}
		}
		prevKey = true;
	}
	else if (CheckHitKey(KEY_INPUT_LEFT)) {
		if (prevKey == false) {
			prevX = cX;
			cX += 1;
			if (cX > x - 1) {
				cX = prevX;
			}
		}
		prevKey = true;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT)) {
		if (prevKey == false) {
			prevX = cX;
			cX -= 1;
			if (cX < 0) {
				cX = prevX;
			}
		}
		prevKey = true;
	}
	else if (CheckHitKey(KEY_INPUT_RETURN)) {
		if (prevKey == false) {

			if (size < getStatus.move) {
				way.push_back({ cX,cY });
			}
		}
		prevKey = true;
	}
	else {
		prevKey = false;
	}

	if (size >= getStatus.move) {
		compWay = true;
	}

	
}



void Icon::SetTriggerParam(MYTRIGGER& _myTrigger)
{
	if (csv_->Load("Assets//Weapon//DefaultWeaponStatus.csv")) {
		width = csv_->GetWidth(0);
		height = csv_->GetHeight();
		for (int x = 0; x < width; x++) {
			if (csv_->GetString(x,0) == "WeaponName") {
				WNLine = x;
			}
			else if (csv_->GetString(x,0) == "Angle") {
				ALine = x;
			}
			else if (csv_->GetString(x,0) == "StartAngle") {
				SALine = x;
			}
			else if (csv_->GetString(x,0) == "RangeSize") {
				RSLine = x;
			}
		}

		for (int i = 0; i < 4; i++) {
			for (int y = 1; y < height  ; y++) {
				if (_myTrigger.Main[i].trigger == csv_->GetString(WNLine, y)) {
					_myTrigger.Main[i].angle = csv_->GetInt(ALine, y);
					_myTrigger.Main[i].startAngle = csv_->GetInt(SALine, y);
					_myTrigger.Main[i].rangeSize = csv_->GetInt(RSLine, y);
					_myTrigger.Main[i].tNum = y;
				}
			}

			for (int y = 1; y < height ; y++) {
				if (_myTrigger.Sub[i].trigger == csv_->GetString(WNLine, y)) {
					_myTrigger.Sub[i].angle = csv_->GetInt(ALine, y);
					_myTrigger.Sub[i].startAngle = csv_->GetInt(SALine, y);
					_myTrigger.Sub[i].rangeSize = csv_->GetInt(RSLine, y);
					_myTrigger.Sub[i].tNum = y;
				}
			}
		}
	}
}
XMINT2 Icon::GetSelectedTrigger(MYTRIGGER _myTrigger)
{
	int main, sub;
	for (int i = 0; i < 4; i++) {
		if (_myTrigger.Main[i].IsSelected) {
			main = i;
		}

		if (_myTrigger.Sub[i].IsSelected) {
			sub = i;
		}
	}
	return XMINT2(main,sub);
}

XMINT2 Icon::GetPlayerOnTileNum()
{
	Player1* pl1 = GetParent()->FindGameObject<Player1>();
	Tile* tile = GetParent()->FindGameObject<Tile>();
	VECTOR Tposition;
	VECTOR Pposition = pl1->GetPosition();
	XMINT2 XY = { 0,0};
	for (int i = 0; i < z; i++) {
		for (int j = 0; j < x; j++) {
			Tposition.x = tile->GetTilesData(i, j).position.x;
			Tposition.y = tile->GetTilesData(i, j).position.y;
			Tposition.z = tile->GetTilesData(i, j).position.z;
			if (Tposition.x == Pposition.x && Tposition.y == Pposition.y && Tposition.z == Pposition.z) {
				XY.x = i;
				XY.y = j;
			}
		}
	}
	return XMINT2(XY.x,XY.y);
}
