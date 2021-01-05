#include "ascii_art.hpp"
#include<fstream>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include<Windows.h>
#endif
//static members initialization
const std::string AsciiImage::ascii_chars = " `^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
															
const int AsciiImage::kNumberOfColors = 255;
const float AsciiImage::kScaleFactor = static_cast<float>(ascii_chars.size() - 1) / kNumberOfColors;


//read image as grayscale(each pixel is represented as one value from 0 to 255)
AsciiImage::AsciiImage(const std::string& file_name) :
	img{cv::imread(file_name,cv::IMREAD_GRAYSCALE)},
	ascii_image{} {
	if (img.empty()) {
		std::cout << "Can't read image properly or this image doesn't exist\n";
	}
	else {
		std::cout << "ASCII iamge could be big, you may want to change the font size of the console\n";
	}
}

//convert image to ascii
void AsciiImage::Convert() {
	if (ascii_image.empty()) {
		for (int y = 0; y < this->img.rows; ++y) {
			const uint8_t* current_pixel = this->img.ptr<uint8_t>(y);
			//map array of pixels to array of chars
			// A = [0..x] ->  B = [0..y](0..255 to 0..ascii_chars.size() - 1)
			//for each t from A, map it to B by multipling t by const factor 'y/x'
			// B[] = '(y/x)*A[t]'
			for (int x = 0; x < this->img.cols; ++x) {
				//KScaleFactor = (65/255) for current ascii chars,
				//max value of pixel = 255, (65/255)*255 =65,
				//so this should not overflow
				size_t index = static_cast<size_t>(std::round(kScaleFactor * static_cast<uint8_t>(current_pixel[x])));
				this->ascii_image.push_back(ascii_chars[index]);
			}
			//add new line
			this->ascii_image.push_back('\r');
			this->ascii_image.push_back('\n');
		}
	}
}

//resize will automaically convert image, so you don't have to conver it manually 
void AsciiImage::ResizeImg(const int width, const int height){
	if (not this->img.empty()) {
		this->ascii_image.clear();
		cv::resize(this->img, this->img, cv::Size{ width,height });
		Convert();
	}
}


//show image at terminal, default color is white
void AsciiImage::ShowImg(const WIN_COLORS color) const {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<int>(color));
#endif
	std::cout << this->ascii_image;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
	SetConsoleTextAttribute(hConsole, static_cast<int>(WIN_COLORS::WHITE));
#endif
}

//save image to text file, colors not preserved
void AsciiImage::SaveAsTxt(const std::string& file_name) const {
	std::ofstream out_file(file_name,std::ios::trunc);
	if(out_file.is_open())
		out_file << this->ascii_image;
}


std::string AsciiImage::GetImageAsString() const {
	return this->ascii_image;
}

std::ostream& operator<<(std::ostream& stream, const AsciiImage& img) {
	std::cout << img.GetImageAsString();
	return stream;
}


