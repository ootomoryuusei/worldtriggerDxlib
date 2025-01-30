#include "csvReader.h"
#include <fstream>
#include <assert.h>

CsvReader::CsvReader()
{
}

CsvReader::CsvReader(std::string filename)
{
	Load(filename);
}

bool CsvReader::Load(std::string filename)
{
	all.clear();

	std::ifstream ifs(filename);
	if (!ifs) return false;

	// BOM Skip����
	unsigned char BOMS[] = { 0xEF, 0xBB, 0xBF };
	bool found = true;
	for (int i=0; i<3; i++) {
		if (ifs.get() != BOMS[i]) {
			found = false;
			break;
		}
	}
	if (!found) {
		ifs.seekg(std::ios_base::beg);
	}

	// �f�[�^��ǂ�
	std::string lineStr;
	while (getline(ifs, lineStr)) {
		while (true) {
			int dq = 0;
			for (int i=0; i<lineStr.size(); i++) {
				if (lineStr[i] == '"')
					dq++;
			}
			if (dq % 2 == 0)
				break;
			std::string s;
			getline(ifs, s);
			lineStr += "\n" + s;
		}
		for (auto it = lineStr.begin(); it!=lineStr.end();) {
			if (*it=='"')
				it = lineStr.erase(it);
			if (it != lineStr.end())
				it++;
		}

		// �s����,�Ő؂蕪����
		LINEREC lineRecord;
		int top = 0;
		bool indq = false;
		for (int n = 0; n < lineStr.size(); n++) {
			if (lineStr[n]==',') {
				if (!indq) {
					lineRecord.record.emplace_back(lineStr.substr(top, (size_t)(n - top)));
					top = n + 1;
				}
			} else if (lineStr[n] == '"')
				indq = !indq;
		}
		lineRecord.record.emplace_back(lineStr.substr(top, lineStr.size() - top));
		all.emplace_back(lineRecord);
	}
	ifs.close();
	return true;
}

CsvReader::~CsvReader()
{
	for (auto rec : all)
		rec.record.clear();
	all.clear();
}

int CsvReader::GetHeight()
{
	return all.size();
}

int CsvReader::GetWidth(int line)
{
	assert(line < GetHeight());
	return all[line].record.size();
}

std::string CsvReader::GetString(int column, int line)
{
	assert(line < GetHeight());
	if (column >= GetWidth(line))
		return "";
	return all[line].record[column];
}

int CsvReader::GetInt(int column, int line)
{
	std::string str = GetString(column, line);
	if (str == "")
		return 0;
	return std::stoi(str);
}

float CsvReader::GetFloat(int column, int line)
{
	std::string str = GetString(column, line);
	if (str == "")
		return 0.0f;
	return std::stof(str);
}
