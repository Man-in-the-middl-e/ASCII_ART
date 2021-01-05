#include "arg_parser.hpp"
#include <unordered_map>



CmdArgs::CmdArgs() :
	path_to_img{},
	out_folder{},
	ascii_img_height{ 0 },
	ascii_img_width{ 0 },
	img_color{ WIN_COLORS::WHITE }
{}

const std::vector<std::pair<std::string, std::string>> Parser::desription{
		{"-p=path", "path to the image, this argument is alway required"},
		{"-h", "print help"},
		{"-c=clr","choose the color of ASCII image,by default -c=WH, works for Windows only"
												 "\n\tWH - white"
												 "\n\tBL - blue"
												 "\n\tLB - light blue"
												 "\n\tGR - green"
												 "\n\tRD - red"
												 "\n\tYL - yellow"
												 "\n\tPR - purple"},
		{"-rs=WxH", "resize ascii img, W - width(number of chars), H - height(number of chars)"},
		{"-s","save the ascii image as .txt file in current directory"}

};

const std::string Parser::keys = "{help h usage ? | |print help msg}"
						  "{path p        | |path to img   }"
						  "{color c		  | |image color   }"
						  "{resize rs     | |resize img    }"
						  "{save s       | |save img      }";



Parser::Parser(int argc, char* argv[]):
	parser{argc,argv,Parser::keys},
	arguments_values{},
	ready{ false }
{
	if (parser.has("help") || argc < 2 || !(ready = parser.has("path"))) {
		PrintHelp(argv[0]);
		return;
	}
	//required arguments
	arguments_values.path_to_img = parser.get<std::string>("path");

	//optinal arguments
	if (parser.has("color")) {
		arguments_values.img_color = DetermineColor(parser.get<std::string>("color"));
	}
	if (parser.has("resize")) {
		std::string img_size = parser.get<std::string>("resize");
		//example:200x200
		size_t delim_pos = img_size.find('x');
		arguments_values.ascii_img_height = std::stoi(img_size.substr(0, delim_pos));
		arguments_values.ascii_img_width = std::stoi(img_size.substr(delim_pos + 1,
			img_size.size() - delim_pos));
		present_optional_arguments.push_back(OPTIONAL_ARGS::SET_SIZE);
	}


	//parse this at the end 
	if (parser.has("save")) {
		arguments_values.out_folder = arguments_values.path_to_img.substr(0,
			arguments_values.path_to_img.rfind('.')) + "ASCII_IMG.txt";
		present_optional_arguments.push_back(OPTIONAL_ARGS::SET_OUT_FOLDER);
	}
}



std::string Parser::GetPathToImg() const {
	return arguments_values.path_to_img;
}

std::string Parser::GetPathToOutImg() const {
	return arguments_values.out_folder;
}

WIN_COLORS Parser::GetColorOfImg() const {
	return arguments_values.img_color;
}

int Parser::GetImgHig() const {
	return arguments_values.ascii_img_height;
}

int Parser::GetImgWdh() const {
	return arguments_values.ascii_img_width;
}

bool Parser::GetStatus() const {
	return ready;
}

std::vector<OPTIONAL_ARGS> Parser::GetOptionalArgs() const {
	return present_optional_arguments;
}


void Parser::PrintHelp(char* argv0) {
	std::cout << "Usage: " << argv0 << " [";
	for (const auto& cmd : Parser::desription) {
		std::cout << cmd.first << (cmd.first != Parser::desription.back().first ? " |" : "]");
	}
	std::cout << "\nDesription: \n";
	for (const auto&[cmd, dscp] : Parser::desription) {
		std::cout << cmd << "\t:" << dscp << "\n";
	}
}
WIN_COLORS Parser::DetermineColor(const std::string& color) const{
std::unordered_map<std::string, WIN_COLORS> colors{
		{"BL",WIN_COLORS::BLUE},
		{"GR",WIN_COLORS::GREEN},
		{"LB",WIN_COLORS::LIGHT_BLUE},
		{"RD",WIN_COLORS::RED},
		{"PR",WIN_COLORS::PURPLE},
		{"YL",WIN_COLORS::YELLOW},
		{"WH",WIN_COLORS::WHITE}
};
	return colors.count(color) != 0 ? colors[color] : WIN_COLORS::WHITE;
}



