#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>

class MapChip
{
public:
	//CSV�t�@�C���ǂݍ���
	void CsvLoad(int mapChipMaxX, int mapChipMaxY, std::string fName);
	//�}�b�v�i���o�[�w��
	int GetChipNum(int x, int y, int mapChipSize, int mapNumber);

private:
	std::vector<std::vector<int>> mapData;
	std::vector<int> mapChipMaxX;
	std::vector<int> mapChipMaxY;
};