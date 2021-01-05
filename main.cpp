#include "ascii_art.hpp"
#include "arg_parser.hpp"


int main(int argc, char* argv[]) {
	Parser parser(argc, argv);

	if (parser.GetStatus()) {
		auto opt_args = parser.GetOptionalArgs();
		AsciiImage img(parser.GetPathToImg());
		img.Convert();
		for (const auto cmd : opt_args) {
			switch (cmd)
			{
			case OPTIONAL_ARGS::SET_OUT_FOLDER:
				img.SaveAsTxt(parser.GetPathToOutImg());
				break;
			case OPTIONAL_ARGS::SET_SIZE:
				img.ResizeImg(parser.GetImgWdh(), parser.GetImgHig());
				break;
			default:
				break;
			}
		}
		img.ShowImg(parser.GetColorOfImg());
	}
	return 0;
}