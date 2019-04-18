#include "BoxBlur.h"



BoxBlur::BoxBlur(int radius)
	: GenericFilter(radius)
{
}


BoxBlur::~BoxBlur()
{
}

void BoxBlur::horizAvg(GenericImage& img, int color, int radius)
{
}

void BoxBlur::verticalAvg(GenericImage& img, int color, int radius)
{
	// TODO
}

void BoxBlur::filter(BitmapImage * out)
{
	//BitmapImage image(out);
	//int radius = 5;					// TODO make radius changable

	//
	//std::thread red(BoxBlur::horizAvg, std::ref(image), 0, radius);
	//std::thread green(BoxBlur::horizAvg, std::ref(image), 1, radius);
	//std::thread blue(BoxBlur::horizAvg, std::ref(image), 2, radius);

	//red.join();
	//green.join();
	//blue.join();

	//red = std::thread(BoxBlur::verticalAvg, std::ref(image), 0, radius);
	//green = std::thread(BoxBlur::verticalAvg, std::ref(image), 1, radius);
	//blue = std::thread(BoxBlur::verticalAvg, std::ref(image), 2, radius);

	//red.join();
	//green.join();
	//blue.join();
}
