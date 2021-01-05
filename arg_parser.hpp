#pragma once
#include "ascii_art.hpp"

class CmdArgs {
public:
	CmdArgs();
	std::string path_to_img;
	std::string out_folder;
	int ascii_img_width;
	int ascii_img_height;
	WIN_COLORS img_color;
};

enum class OPTIONAL_ARGS : uint8_t {
	SET_SIZE,
	SET_OUT_FOLDER
};

class Parser {
public:
	Parser(int argc, char* argv[]);
	std::string GetPathToImg() const;
	std::string GetPathToOutImg() const;
	WIN_COLORS GetColorOfImg() const;
	std::vector<OPTIONAL_ARGS> GetOptionalArgs() const;
	int GetImgWdh() const;
	int GetImgHig() const;
	bool GetStatus() const;
private:
	CmdArgs arguments_values;
	cv::CommandLineParser parser;
	std::vector<OPTIONAL_ARGS> present_optional_arguments;
	bool ready; // not the best way to handle errors
	const static std::string keys;
	const static std::vector<std::pair<std::string, std::string>>  desription;

	void PrintHelp(char* argv0);
	WIN_COLORS DetermineColor(const std::string& color) const;
};


