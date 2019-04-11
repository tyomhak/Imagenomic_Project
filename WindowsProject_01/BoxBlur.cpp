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
	unsigned int curRow = 0;
	while (curRow < img._width)
	{
		unsigned int curCol = 0;
		long double avgSum = 0.0;
		int i = -radius + 1;
		unsigned int size = 0;

		while (i < radius)
		{
			if (i < 0)
				continue;
			else
			{
				avgSum += img.GetPixel(curRow, i)[color];
				++size;
			}
			++i;
		}

		if (size < 1)
			throw("radius < 1");

		// update pixel, remove left, add right to average
		while (curCol < img._height)
		{
			img.GetPixel(curRow, curCol)[color] = avgSum / size;


			if (curCol - radius < -1)
			{
				avgSum -= img.GetPixel(curRow, curCol - radius + 1)[color];
			}
			else
				++size;


			if (curCol + radius < img._height)
			{
				avgSum += img.GetPixel(curRow, curCol + radius)[color];
			}
			else
				--size;


			++curCol;
		}

		++curRow;
	}
}


void BoxBlur::verticalAvg(GenericImage& img, int color, int radius)
{
	// TODO
}

void BoxBlur::filter(Bitmap * out)
{
	GenericImage image(out);
	int radius = 5;					// TODO make radius changable

	
	std::thread red(BoxBlur::horizAvg, std::ref(image), 0, radius);
	std::thread green(BoxBlur::horizAvg, std::ref(image), 1, radius);
	std::thread blue(BoxBlur::horizAvg, std::ref(image), 2, radius);

	red.join();
	green.join();
	blue.join();

	red = std::thread(BoxBlur::verticalAvg, std::ref(image), 0, radius);
	green = std::thread(BoxBlur::verticalAvg, std::ref(image), 1, radius);
	blue = std::thread(BoxBlur::verticalAvg, std::ref(image), 2, radius);

	red.join();
	green.join();
	blue.join();
}
