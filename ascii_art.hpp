#pragma once

#include<array>
#include<string>
#include<opencv2/opencv.hpp>

enum class WIN_COLORS : uint8_t {
	BLUE = 9,
	GREEN,
	LIGHT_BLUE,
	RED,
	PURPLE,
	YELLOW,
	WHITE
};



class AsciiImage {
public:
	AsciiImage(const std::string& file_name);
	void Convert();
	void ResizeImg(const int width, const int height);
	void ShowImg(const WIN_COLORS color = WIN_COLORS::WHITE) const;
	void SaveAsTxt(const std::string& file_name) const;

	std::string GetImageAsString() const;
	friend std::ostream& operator<<(std::ostream& stream, const AsciiImage& img);
private:
	cv::Mat img;
	std::string ascii_image;
	static const std::string ascii_chars;
	static const int kNumberOfColors;
	static const float kScaleFactor;
};
